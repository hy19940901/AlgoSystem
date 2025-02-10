#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <iostream>

// Type alias for the task and callback functions
using Task = std::function<void()>;
using Callback = std::function<void(int)>;

/**
 * @class ThreadPool
 * @brief A simple thread pool implementation.
 *
 * This class manages a pool of worker threads that can execute tasks asynchronously.
 */
class ThreadPool {
public:
    /**
     * @brief Constructs a thread pool with a specified number of threads.
     * @param threads The number of threads in the pool.
     */
    ThreadPool(size_t threads);

    /**
     * @brief Destructor that ensures all worker threads finish execution.
     */
    ~ThreadPool();

    /**
     * @brief Adds a new task to the thread pool.
     * @param task The task to be executed, encapsulated in a std::function.
     * @param callback A callback function to be executed after the task completion.
     * @return A std::future<void> that can be used to wait for the task to complete.
     */
    std::future<void> enqueue(Task task, Callback callback);

private:
    /**
     * @brief Function for each worker thread to execute tasks from the queue.
     */
    void workerThread();

    std::vector<std::thread> workers;                  ///< Container for worker threads
    std::queue<std::pair<Task, Callback>> tasks;       ///< Queue for storing tasks and their callbacks

    std::mutex queueMutex;                             ///< Mutex to protect the task queue
    std::condition_variable condition;                 ///< Condition variable for task synchronization
    bool stop;                                         ///< Flag to indicate if the thread pool should stop
};

#endif // THREADPOOL_H
