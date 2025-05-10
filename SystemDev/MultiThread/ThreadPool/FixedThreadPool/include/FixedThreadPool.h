// FixedThreadPool.h
#ifndef FIXED_THREAD_POOL_H
#define FIXED_THREAD_POOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <atomic>

/**
 * @brief A simplified non-template thread pool.
 *        Only supports std::function<void()> tasks with optional callback.
 */
class FixedThreadPool {
public:
    explicit FixedThreadPool(size_t thread_count);
    ~FixedThreadPool();

    std::future<void> submit(std::function<void()> task);
    void submit(std::function<void()> task, std::function<void()> callback);

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    std::atomic<bool> stop_flag;
};

#endif // FIXED_THREAD_POOL_H
