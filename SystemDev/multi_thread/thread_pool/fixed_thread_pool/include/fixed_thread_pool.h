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
    explicit FixedThreadPool(size_t threadCount);
    ~FixedThreadPool();

    std::future<void> Submit(std::function<void()> task);
    void Submit(std::function<void()> task, std::function<void()> callback);

private:
    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;
    std::mutex queueMutex_;
    std::condition_variable condition_;
    std::atomic<bool> stopFlag_;
};

#endif  // FIXED_THREAD_POOL_H
