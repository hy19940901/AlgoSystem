#include "ThreadedServer.h"
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
void handleSignal(int signal) {
    if (signal == SIGINT || signal == SIGTERM) {
        std::cout << "\n[Signal] Caught signal " << signal << ", stopping server...\n";
        if (ThreadedServer::instance) {
            ThreadedServer::instance->stop();  // Delegate stop to server instance
        }
    }
}

// Constructor initializes port, epoll fd, and thread pool
ThreadedServer::ThreadedServer(int port, int threadCount)
    : port_(port), serverFd_(-1), epollFd_(-1), pool_(threadCount) {}

// Destructor ensures resources are released
ThreadedServer::~ThreadedServer() {
    if (serverFd_ != -1) close(serverFd_);
    if (epollFd_ != -1) close(epollFd_);
    pool_.join();  // Wait for all threads to complete
}

// Called by signal handler to set stop flag
void ThreadedServer::stop() {
    stopFlag_ = true;
}

// Set file descriptor to non-blocking mode
void ThreadedServer::setNonBlocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

// Set up server socket, bind, listen, and register with epoll
void ThreadedServer::setupServer() {
    serverFd_ = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(serverFd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port_);
    bind(serverFd_, (sockaddr*)&addr, sizeof(addr));
    listen(serverFd_, SOMAXCONN);
    setNonBlocking(serverFd_);

    epollFd_ = epoll_create1(0);
    epoll_event ev{};
    ev.data.fd = serverFd_;
    ev.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollFd_, EPOLL_CTL_ADD, serverFd_, &ev);

    std::cout << "HTTP Mock Server listening on port " << port_ << std::endl;
}

// Accept all new client connections until queue is empty
void ThreadedServer::acceptClients() {
    while (true) {
        sockaddr_in client{};
        socklen_t len = sizeof(client);
        int clientFd = accept(serverFd_, (sockaddr*)&client, &len);
        if (clientFd < 0) break;

        setNonBlocking(clientFd);
        epoll_event ev{};
        ev.data.fd = clientFd;
        ev.events = EPOLLIN | EPOLLET;
        epoll_ctl(epollFd_, EPOLL_CTL_ADD, clientFd, &ev);
    }
}

// Generate a simulated HTTP JSON response with 1MB payload
std::unique_ptr<std::string> ThreadedServer::getHttpResponse(const std::string& method, const std::string& path) {
    std::ostringstream bodyStream;
    bodyStream << "{\n"
               << "  \"method\": \"" << method << "\",\n"
               << "  \"path\": \"" << path << "\",\n"
               << "  \"data\": \"" << std::string(1024 * 1024, 'X') << "\",\n"
               << "  \"timestamp\": " << std::time(nullptr) << "\n"
               << "}";
    std::string body = bodyStream.str();

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
void ThreadedServer::handleClient(int clientFd) {
    char buffer[4096] = {0};
    ssize_t count = read(clientFd, buffer, sizeof(buffer) - 1);
    if (count <= 0) {
        close(clientFd);
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

    auto response = getHttpResponse(method, path);
    send(clientFd, response->c_str(), response->size(), 0);
    close(clientFd);
}

// Main server loop using epoll and thread pool to handle clients
void ThreadedServer::run() {
    signal(SIGINT, handleSignal);
    signal(SIGTERM, handleSignal);
    setupServer();
    epoll_event* events = new epoll_event[maxEvents_];

    while (!stopFlag_) {
        int n = epoll_wait(epollFd_, events, maxEvents_, 1000); // timeout = 1s
        for (int i = 0; i < n; ++i) {
            int fd = events[i].data.fd;
            if (fd == serverFd_) {
                acceptClients();
            } else {
                boost::asio::post(pool_, [this, fd]() {
                    handleClient(fd);
                });
            }
        }
    }

    std::cout << "[Server] Graceful shutdown requested. Exiting..." << std::endl;
    delete[] events;
}
