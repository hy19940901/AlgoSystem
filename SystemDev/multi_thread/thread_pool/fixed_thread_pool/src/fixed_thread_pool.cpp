#include "../include/fixed_thread_pool.h"
#include <stdexcept>

FixedThreadPool::FixedThreadPool(size_t threadCount) : stopFlag_(false) {
    for (size_t i = 0; i < threadCount; ++i) {
        workers_.emplace_back([this] {
            while (true) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(queueMutex_);
                    condition_.wait(lock, [this] {
                        return stopFlag_ || !tasks_.empty();
                    });
                    if (stopFlag_ && tasks_.empty()) return;
                    task = std::move(tasks_.front());
                    tasks_.pop();
                }
                task();
            }
        });
    }
}

FixedThreadPool::~FixedThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queueMutex_);
        stopFlag_ = true;
    }
    condition_.notify_all();
    for (std::thread& worker : workers_) {
        if (worker.joinable()) worker.join();
    }
}

std::future<void> FixedThreadPool::Submit(std::function<void()> task) {
    auto taskPtr = std::make_shared<std::packaged_task<void()>>(std::move(task));
    std::future<void> res = taskPtr->get_future();

    {
        std::unique_lock<std::mutex> lock(queueMutex_);
        if (stopFlag_) throw std::runtime_error("ThreadPool stopped");
        tasks_.emplace([taskPtr]() { (*taskPtr)(); });
    }
    condition_.notify_one();
    return res;
}

void FixedThreadPool::Submit(std::function<void()> task, std::function<void()> callback) {
    {
        std::unique_lock<std::mutex> lock(queueMutex_);
        if (stopFlag_) throw std::runtime_error("ThreadPool stopped");
        tasks_.emplace([task, callback]() {
            task();
            callback();
        });
    }
    condition_.notify_one();
}
