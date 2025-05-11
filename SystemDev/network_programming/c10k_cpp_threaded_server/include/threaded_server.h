#ifndef THREADED_SERVER_H_
#define THREADED_SERVER_H_

#include <boost/asio.hpp>
#include <atomic>
#include <memory>
#include <string>

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
   * @param thread_count Number of threads to initialize in the thread pool
   */
  ThreadedServer(int port, int thread_count);

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
  int server_fd_;               ///< File descriptor for the server socket
  int epoll_fd_;                ///< File descriptor for epoll instance
  int max_events_ = 10000;      ///< Max number of events per epoll_wait call
  boost::asio::thread_pool pool_; ///< Boost thread pool for concurrent task execution
  std::atomic<bool> stop_flag_{false}; ///< Atomic flag for shutdown coordination

  /**
   * @brief Initialize socket, bind, listen, and epoll registration
   */
  void setup_server();

  /**
   * @brief Set a socket file descriptor to non-blocking mode
   * @param fd File descriptor to modify
   */
  void set_non_blocking(int fd);

  /**
   * @brief Accept all pending client connections from the server socket
   */
  void accept_clients();

  /**
   * @brief Handle individual client request/response cycle
   * @param client_fd File descriptor of the accepted client socket
   */
  void handle_client(int client_fd);

  /**
   * Generate a complete HTTP response with dynamic JSON payload.
   * @param method HTTP method from client request.
   * @param path Path from client request.
   * @return Smart pointer holding full HTTP response.
   */
  std::unique_ptr<std::string> get_http_response(const std::string& method, const std::string& path);
};

#endif  // THREADED_SERVER_H_
