#ifndef THREADED_SERVER_H
#define THREADED_SERVER_H

#include <boost/asio/thread_pool.hpp>
#include <boost/asio/post.hpp>
#include <string>
#include <atomic>
#include <memory>

/**
 * @class ThreadedServer
 * @brief A high-performance HTTP mock server using epoll and Boost thread pool.
 *
 * This server handles thousands of concurrent connections using non-blocking sockets
 * and a scalable thread pool. It supports graceful shutdown on SIGINT/SIGTERM.
 */
class ThreadedServer {
public:
    /**
     * @brief Construct a new ThreadedServer object
     * @param port The port number the server will listen on
     * @param threadCount Number of threads to initialize in the thread pool
     */
    ThreadedServer(int port, int threadCount);

    /**
     * @brief Destroy the ThreadedServer object, closing all resources
     */
    ~ThreadedServer();

    /**
     * @brief Run the server event loop (blocking call)
     */
    void run();

    /**
     * @brief Set the stop flag to initiate graceful shutdown
     */
    void stop();

    /**
     * @brief Global pointer used in signal handling for safe shutdown
     */
    static ThreadedServer* instance;

private:
    int port_;                    ///< Listening port
    int serverFd_;                ///< File descriptor for the server socket
    int epollFd_;                 ///< File descriptor for epoll instance
    int maxEvents_ = 10000;       ///< Max number of events per epoll_wait call
    boost::asio::thread_pool pool_; ///< Boost thread pool for concurrent task execution
    std::atomic<bool> stopFlag_{false}; ///< Atomic flag for shutdown coordination

    /**
     * @brief Initialize socket, bind, listen, and epoll registration
     */
    void setupServer();

    /**
     * @brief Set a socket file descriptor to non-blocking mode
     * @param fd File descriptor to modify
     */
    void setNonBlocking(int fd);

    /**
     * @brief Accept all pending client connections from the server socket
     */
    void acceptClients();

    /**
     * @brief Handle individual client request/response cycle
     * @param clientFd File descriptor of the accepted client socket
     */
    void handleClient(int clientFd);

    /**
     * Generate a complete HTTP response with dynamic JSON payload.
     * @param method HTTP method from client request.
     * @param path Path from client request.
     * @return Smart pointer holding full HTTP response.
     */
    std::unique_ptr<std::string> getHttpResponse(const std::string& method, const std::string& path);
};

#endif // THREADED_SERVER_H
