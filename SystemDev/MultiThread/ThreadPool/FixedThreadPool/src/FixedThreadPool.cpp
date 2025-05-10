#include "../include/FixedThreadPool.h"
#include <stdexcept>

FixedThreadPool::FixedThreadPool(size_t thread_count) : stop_flag(false) {
    for (size_t i = 0; i < thread_count; ++i) {
        workers.emplace_back([this] {
            while (true) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(queue_mutex);
                    condition.wait(lock, [this] {
                        return stop_flag || !tasks.empty();
                    });
                    if (stop_flag && tasks.empty()) return;
                    task = std::move(tasks.front());
                    tasks.pop();
                }
                task();
            }
        });
    }
}

FixedThreadPool::~FixedThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop_flag = true;
    }
    condition.notify_all();
    for (std::thread& worker : workers) {
        if (worker.joinable()) worker.join();
    }
}

std::future<void> FixedThreadPool::submit(std::function<void()> task) {
    auto task_ptr = std::make_shared<std::packaged_task<void()>>(std::move(task));
    std::future<void> res = task_ptr->get_future();

    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        if (stop_flag) throw std::runtime_error("ThreadPool stopped");
        tasks.emplace([task_ptr]() { (*task_ptr)(); });
    }
    condition.notify_one();
    return res;
}

void FixedThreadPool::submit(std::function<void()> task, std::function<void()> callback) {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        if (stop_flag) throw std::runtime_error("ThreadPool stopped");
        tasks.emplace([task, callback]() {
            task();
            callback();
        });
    }
    condition.notify_one();
}
