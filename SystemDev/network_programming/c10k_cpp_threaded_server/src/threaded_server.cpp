#include "../include/threaded_server.h"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sstream>
#include <ctime>
#include <csignal>

// Static instance pointer for signal-safe access
ThreadedServer* ThreadedServer::instance = nullptr;

// Signal handler to initiate graceful shutdown
void handle_signal(int signal) {
    if (signal == SIGINT || signal == SIGTERM) {
        std::cout << "\n[Signal] Caught signal " << signal << ", stopping server...\n";
        if (ThreadedServer::instance) {
            ThreadedServer::instance->stop();  // Delegate stop to server instance
        }
    }
}

// Constructor initializes port, epoll fd, and thread pool
ThreadedServer::ThreadedServer(int port, int thread_count)
        : port_(port), server_fd_(-1), epoll_fd_(-1), pool_(thread_count) {}

// Destructor ensures resources are released
ThreadedServer::~ThreadedServer() {
    if (server_fd_ != -1) close(server_fd_);
    if (epoll_fd_ != -1) close(epoll_fd_);
    pool_.join();  // Wait for all threads to complete
}

// Called by signal handler to set stop flag
void ThreadedServer::stop() {
    stop_flag_ = true;
}

// Set file descriptor to non-blocking mode
void ThreadedServer::set_non_blocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

// Set up server socket, bind, listen, and register with epoll
void ThreadedServer::setup_server() {
    server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server_fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port_);
    bind(server_fd_, (sockaddr*)&addr, sizeof(addr));
    listen(server_fd_, SOMAXCONN);
    set_non_blocking(server_fd_);

    epoll_fd_ = epoll_create1(0);
    epoll_event ev{};
    ev.data.fd = server_fd_;
    ev.events = EPOLLIN | EPOLLET;
    epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, server_fd_, &ev);

    std::cout << "HTTP Mock Server listening on port " << port_ << std::endl;
}

// Accept all new client connections until queue is empty
void ThreadedServer::accept_clients() {
    while (true) {
        sockaddr_in client{};
        socklen_t len = sizeof(client);
        int client_fd = accept(server_fd_, (sockaddr*)&client, &len);
        if (client_fd < 0) break;

        set_non_blocking(client_fd);
        epoll_event ev{};
        ev.data.fd = client_fd;
        ev.events = EPOLLIN | EPOLLET;
        epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, client_fd, &ev);
    }
}

// Generate a simulated HTTP JSON response with 1MB payload
std::unique_ptr<std::string> ThreadedServer::get_http_response(const std::string& method, const std::string& path) {
    std::ostringstream body_stream;
    body_stream << "{\n"
                << "    \"method\": \"" << method << "\",\n"
                << "    \"path\": \"" << path << "\",\n"
                << "    \"data\": \"" << std::string(1024 * 1024, 'X') << "\",\n"
                << "    \"timestamp\": " << std::time(nullptr) << "\n"
                << "}";
    std::string body = body_stream.str();

    std::ostringstream header;
    header << "HTTP/1.1 200 OK\r\n"
           << "Content-Type: application/json\r\n"
           << "Content-Length: " << body.size() << "\r\n"
           << "Connection: close\r\n"
           << "\r\n";

    auto response = std::make_unique<std::string>();
    *response = header.str() + body;
    return response;
}

// Read client request and respond with simulated HTTP JSON
void ThreadedServer::handle_client(int client_fd) {
    char buffer[4096] = {0};
    ssize_t count = read(client_fd, buffer, sizeof(buffer) - 1);
    if (count <= 0) {
        close(client_fd);
        return;
    }

    std::string request(buffer);
    std::string method = "UNKNOWN";
    std::string path = "/";

    size_t method_end = request.find(' ');
    if (method_end != std::string::npos) {
        method = request.substr(0, method_end);
        size_t path_end = request.find(' ', method_end + 1);
        if (path_end != std::string::npos)
            path = request.substr(method_end + 1, path_end - method_end - 1);
    }

    auto response = get_http_response(method, path);
    send(client_fd, response->c_str(), response->size(), 0);
    close(client_fd);
}

// Main server loop using epoll and thread pool to handle clients
void ThreadedServer::run() {
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);
    setup_server();
    epoll_event* events = new epoll_event[max_events_];

    while (!stop_flag_) {
        int n = epoll_wait(epoll_fd_, events, max_events_, 1000); // timeout = 1s
        for (int i = 0; i < n; ++i) {
            int fd = events[i].data.fd;
            if (fd == server_fd_) {
                accept_clients();
            } else {
                boost::asio::post(pool_, [this, fd]() {
                    handle_client(fd);
                });
            }
        }
    }

    std::cout << "[Server] Graceful shutdown requested. Exiting..." << std::endl;
    delete[] events;
}
