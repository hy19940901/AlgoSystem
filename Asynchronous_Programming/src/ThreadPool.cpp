#include "../include/ThreadPool.h"

/**
 * @brief Thread pool constructor, initializes the specified number of worker threads.
 * @param threads The number of threads to be created in the pool.
 */
ThreadPool::ThreadPool(size_t threads) : stop(false) {
    for (size_t i = 0; i < threads; ++i) {
        workers.emplace_back([this] { workerThread(); });
    }
}

/**
 * @brief Thread pool destructor, ensures all threads complete before destruction.
 */
ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stop = true;  // Set stop flag to true
    }
    condition.notify_all();  // Notify all threads to wake up
    for (std::thread &worker : workers) {
        worker.join();  // Wait for all worker threads to complete
    }
}

/**
 * @brief Adds a new task to the thread pool's task queue.
 * @param task The task to be executed.
 * @param callback The callback to execute after the task is completed.
 * @return A future object that can be used to wait for task completion.
 * @throws std::runtime_error If the thread pool is stopped.
 */
std::future<void> ThreadPool::enqueue(Task task, Callback callback) {
    auto packagedTask = std::make_shared<std::packaged_task<void()>>(task);
    std::future<void> result = packagedTask->get_future();
    
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        if (stop) {
            throw std::runtime_error("enqueue on stopped ThreadPool");
        }
        tasks.emplace([packagedTask]() { (*packagedTask)(); }, callback);
    }

    condition.notify_one();  // Notify one worker thread to pick up the new task
    return result;
}

/**
 * @brief The main function for worker threads to execute tasks from the queue.
 * This function runs in a loop, picking up tasks from the queue and executing them.
 */
void ThreadPool::workerThread() {
    while (true) {
        std::pair<Task, Callback> taskPair;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            condition.wait(lock, [this] { return stop || !tasks.empty(); });
            if (stop && tasks.empty()) {
                return;  // Exit if stop flag is set and no tasks remain
            }

            taskPair = std::move(tasks.front());  // Get the task from the front of the queue
            tasks.pop();  // Remove the task from the queue
        }

        taskPair.first();  // Execute the task
        taskPair.second(42);  // Execute the callback with a sample result (42)
    }
}
