// ThreadPool.hpp
#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <atomic>

/**
 * @brief A modern, thread-safe thread pool.
 *        - submit(): template, returns future
 *        - post(): non-template, for void tasks
 */
class ThreadPool {
public:
    explicit ThreadPool(size_t thread_count) : stop_flag(false) {
        for (size_t i = 0; i < thread_count; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    Task task;
                    {
                        std::unique_lock<std::mutex> lock(queue_mutex);
                        condition.wait(lock, [this] {
                            return stop_flag || !tasks.empty();
                        });
                        if (stop_flag && tasks.empty())
                            return;
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop_flag = true;
        }
        condition.notify_all();
        for (std::thread &worker : workers)
            worker.join();
    }

    /**
     * @brief Submit a task and return a future.
     *        Task can have return value.
     */
    template <class F, class... Args>
    auto submit(F&& f, Args&&... args)
        -> std::future<typename std::invoke_result<F, Args...>::type> {
        using return_type = typename std::invoke_result<F, Args...>::type;

        auto task_ptr = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<return_type> res = task_ptr->get_future();
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            if (stop_flag)
                throw std::runtime_error("ThreadPool has been stopped");
            tasks.emplace([task_ptr]() { (*task_ptr)(); });
        }
        condition.notify_one();
        return res;
    }

    /**
     * @brief Post a task with no return value (fire-and-forget style).
     *        Task must be std::function<void()>.
     */
    void post(std::function<void()> task) {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            if (stop_flag)
                throw std::runtime_error("ThreadPool has been stopped");
            tasks.emplace(std::move(task));
        }
        condition.notify_one();
    }

private:
    using Task = std::function<void()>;

    std::vector<std::thread> workers;
    std::queue<Task> tasks;

    std::mutex queue_mutex;
    std::condition_variable condition;
    std::atomic<bool> stop_flag;
};

#endif // THREAD_POOL_HPP


/**
 * @brief SimpleThreadPool: a minimal thread pool version without templates.
 *        Accepts only std::function<void()> tasks via post().
 *        No return values (fire-and-forget only).
 */
class SimpleThreadPool {
public:
    explicit SimpleThreadPool(size_t threads) : stop_flag(false) {
        for (size_t i = 0; i < threads; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(queue_mutex);
                        condition.wait(lock, [this] {
                            return stop_flag || !tasks.empty();
                        });
                        if (stop_flag && tasks.empty())
                            return;
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    ~SimpleThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop_flag = true;
        }
        condition.notify_all();
        for (std::thread& worker : workers)
            worker.join();
    }

    // Post a void task, no return
    void post(const std::function<void()>& task) {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            if (stop_flag)
                throw std::runtime_error("SimpleThreadPool has been stopped");
            tasks.push(task);
        }
        condition.notify_one();
    }

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queue_mutex;
    std::condition_variable condition;
    std::atomic<bool> stop_flag;
};

