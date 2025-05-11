#include "../include/cpp20_thread.h"

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <cmath>
#include <future>
#include <queue>
#include <condition_variable>
#include <semaphore>
#include <barrier>
#include <mutex>
#include <shared_mutex>
#include <atomic>
#include <stdexcept>
#include <algorithm>

namespace thread_demo {

void BasicThreadsDemo::Run() {
    std::cout << "=== Thread Creation Demo ===" << std::endl;
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([i]() {
            const int work_size = 8'000'000 + i * 2'000'000;
            double result = 0.0;
            auto start = std::chrono::high_resolution_clock::now();
            for (int j = 1; j < work_size; ++j) {
                result += std::sqrt(j * 1.0);
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << "[Thread " << i << "] finished in " << elapsed << " ms. Result: " << static_cast<long long>(result) << std::endl;
        });
    }
    for (auto& t : threads) {
        t.join();
    }
}

void DetachedThreadsDemo::Run() {
    std::cout << "\n=== Detached Threads Demo ===" << std::endl;
    std::thread([]() {
        std::cout << "[Detached Thread] Running..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "[Detached Thread] Done." << std::endl;
    }).detach();
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void MutexDemo::Run() {
    counter_ = 0;
    std::thread t1(&MutexDemo::Worker, this);
    std::thread t2(&MutexDemo::Worker, this);
    t1.join();
    t2.join();
    std::cout << "[MutexDemo] Final counter value: " << counter_ << std::endl;
}

void MutexDemo::Worker() {
    for (int i = 0; i < 100000; ++i) {
        std::lock_guard<std::mutex> lock(mutex_);
        ++counter_;
    }
}

void ConditionDemo::Run() {
    ready_ = false;
    std::thread waiter(&ConditionDemo::Waiter, this);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> lock(mutex_);
        ready_ = true;
    }
    cv_.notify_one();
    waiter.join();
}

void ConditionDemo::Waiter() {
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [this] { return ready_; });
    std::cout << "[ConditionDemo] Waiter received signal." << std::endl;
}

void RwlockDemo::Run() {
    shared_data_ = 0;
    std::thread reader1(&RwlockDemo::ReaderTask, this, 1);
    std::thread writer(&RwlockDemo::WriterTask, this);
    std::thread reader2(&RwlockDemo::ReaderTask, this, 2);
    reader1.join();
    writer.join();
    reader2.join();
}

void RwlockDemo::ReaderTask(int id) {
    std::shared_lock lock(rw_mutex_);
    std::cout << "[Reader " << id << "] Read: " << shared_data_ << std::endl;
}

void RwlockDemo::WriterTask() {
    std::unique_lock lock(rw_mutex_);
    ++shared_data_;
    std::cout << "[Writer] Updated data to: " << shared_data_ << std::endl;
}

void BarrierDemo::Run() {
    std::thread t1(&BarrierDemo::Task, this, 1);
    std::thread t2(&BarrierDemo::Task, this, 2);
    std::thread t3(&BarrierDemo::Task, this, 3);
    t1.join();
    t2.join();
    t3.join();
}

void BarrierDemo::Task(int id) {
    std::cout << "[Thread " << id << "] waiting at barrier..." << std::endl;
    sync_point_.arrive_and_wait();
    std::cout << "[Thread " << id << "] passed the barrier." << std::endl;
}

thread_local int TlsDemo::tls_var_ = 0;

void TlsDemo::Run() {
    std::thread t1(&TlsDemo::Task, this, 1);
    std::thread t2(&TlsDemo::Task, this, 2);
    t1.join();
    t2.join();
}

void TlsDemo::Task(int id) {
    tls_var_ = id * 10;
    std::cout << "[Thread " << id << "] TLS var = " << tls_var_ << std::endl;
}

void SpinlockDemo::Run() {
    counter_ = 0;
    std::thread t1(&SpinlockDemo::Worker, this);
    std::thread t2(&SpinlockDemo::Worker, this);
    t1.join();
    t2.join();
    std::cout << "[SpinlockDemo] Final counter: " << counter_ << std::endl;
}

void SpinlockDemo::Worker() {
    for (int i = 0; i < 100000; ++i) {
        while (spinlock_.test_and_set(std::memory_order_acquire)) {}
        ++counter_;
        spinlock_.clear(std::memory_order_release);
    }
}

void SemaphoreDemo::Run() {
    counter_ = 0;
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(&SemaphoreDemo::Worker, this, i);
    }
    for (auto& t : threads) {
        t.join();
    }
    std::cout << "[SemaphoreDemo] Total threads passed: " << counter_ << std::endl;
}

void SemaphoreDemo::Worker(int id) {
    sem_.acquire();
    std::cout << "[Thread " << id << "] entered." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    ++counter_;
    std::cout << "[Thread " << id << "] exiting." << std::endl;
    sem_.release();
}

void ProducerConsumerDemo::Run() {
    std::thread prod(&ProducerConsumerDemo::Producer, this);
    std::thread cons1(&ProducerConsumerDemo::Consumer, this, 1);
    std::thread cons2(&ProducerConsumerDemo::Consumer, this, 2);
    prod.join();
    cons1.join();
    cons2.join();
}

void ProducerConsumerDemo::Producer() {
    for (int i = 1; i <= 10; ++i) {
        std::unique_lock lock(mutex_);
        cv_.wait(lock, [this] { return static_cast<int>(buffer_.size()) < kMaxBuffer; });
        buffer_.push(i);
        std::cout << "[Producer] Produced: " << i << std::endl;
        cv_.notify_all();
    }
    done_ = true;
    cv_.notify_all();
}

void ProducerConsumerDemo::Consumer(int id) {
    while (true) {
        std::unique_lock lock(mutex_);
        cv_.wait(lock, [this] { return !buffer_.empty() || done_; });
        if (buffer_.empty() && done_) break;
        int val = buffer_.front(); buffer_.pop();
        std::cout << "[Consumer " << id << "] Consumed: " << val << std::endl;
        cv_.notify_all();
    }
}

void CancellationDemo::Run() {
    cancel_flag_ = false;
    std::thread worker(&CancellationDemo::Worker, this);
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    cancel_flag_ = true;
    worker.join();
}

void CancellationDemo::Worker() {
    for (int i = 0; i < 10; ++i) {
        if (cancel_flag_.load()) {
            std::cout << "[Worker] Cancelled early." << std::endl;
            return;
        }
        std::cout << "[Worker] Working..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

void ThreadBenchmarkDemo::Run() {
    const int num_threads = 4;
    const int num_iterations = 10'000'000;

    int counter_single = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_threads * num_iterations; ++i) {
        ++counter_single;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "[Single-thread] Time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms, Result: " << counter_single << std::endl;

    int counter_mutex = 0;
    std::mutex mtx;
    start = std::chrono::high_resolution_clock::now();
    {
        std::vector<std::thread> threads;
        for (int i = 0; i < num_threads; ++i) {
            threads.emplace_back([&]() {
                for (int j = 0; j < num_iterations; ++j) {
                    std::lock_guard lock(mtx);
                    ++counter_mutex;
                }
            });
        }
        for (auto& t : threads) t.join();
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "[Multi-thread mutex] Time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms, Result: " << counter_mutex << std::endl;

    std::atomic<int> counter_atomic = 0;
    start = std::chrono::high_resolution_clock::now();
    {
        std::vector<std::thread> threads;
        for (int i = 0; i < num_threads; ++i) {
            threads.emplace_back([&]() {
                for (int j = 0; j < num_iterations; ++j) {
                    ++counter_atomic;
                }
            });
        }
        for (auto& t : threads) t.join();
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "[Multi-thread atomic] Time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms, Result: " << counter_atomic.load() << std::endl;
}

void ParallelVsSerialDemo::Run() {
    const int num_threads = 4;
    const int N = 40'000'000;
    std::vector<int> data(N, 1);

    auto heavy_compute = [](int& x) {
        for (int i = 0; i < 100; ++i) {
            x = (x * 31 + 7) % 100000;
        }
    };

    auto start = std::chrono::high_resolution_clock::now();
    for (int& x : data) {
        heavy_compute(x);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "[Serial] Time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    std::fill(data.begin(), data.end(), 1);

    start = std::chrono::high_resolution_clock::now();
    std::vector<std::thread> threads;
    int chunk = N / num_threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&, i]() {
            int begin = i * chunk;
            int end = (i == num_threads - 1) ? N : begin + chunk;
            for (int j = begin; j < end; ++j) {
                heavy_compute(data[j]);
            }
        });
    }
    for (auto& t : threads) t.join();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "[Parallel] Time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
}

}  // namespace thread_demo

namespace future_demo {

void FutureDemo::Run() {
    std::cout << "\n=== Future / Async Demo ===" << std::endl;
    auto factorial = [](int n) -> int {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        int result = 1;
        for (int i = 2; i <= n; ++i) result *= i;
        return result;
    };
    std::future<int> fut = std::async(std::launch::async, factorial, 5);
    std::cout << "Doing other work while waiting for future..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    int result = fut.get();
    std::cout << "Factorial(5) = " << result << std::endl;
}

void PackagedTaskDemo::Run() {
    std::cout << "\n=== Packaged Task Demo ===" << std::endl;
    std::packaged_task<int(int)> task([](int x) {
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        return x * x;
    });
    std::future<int> fut = task.get_future();
    std::thread t(std::move(task), 7);
    std::cout << "Square = " << fut.get() << std::endl;
    t.join();
}

void SharedFutureDemo::Run() {
    std::cout << "\n=== Shared Future Demo ===" << std::endl;
    std::promise<std::string> prom;
    std::shared_future<std::string> sfut = prom.get_future().share();
    auto reader = [](std::shared_future<std::string> f, int id) {
        std::cout << "[Reader " << id << "] got: " << f.get() << std::endl;
    };
    std::thread t1(reader, sfut, 1);
    std::thread t2(reader, sfut, 2);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    prom.set_value("shared result");
    t1.join();
    t2.join();
}

void WaitForDemo::Run() {
    std::cout << "\n=== Future wait_for() Demo ===" << std::endl;
    std::future<int> fut = std::async(std::launch::async, [] {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return 100;
    });
    if (fut.wait_for(std::chrono::milliseconds(1000)) == std::future_status::timeout) {
        std::cout << "Timeout: task still running\n";
    } else {
        std::cout << "Result = " << fut.get() << std::endl;
    }
}

void PromiseDemo::Run() {
    std::cout << "\n=== Promise Value Demo ===" << std::endl;
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();
    std::thread t([&prom]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        prom.set_value(42);
    });
    std::cout << "Promise set value = " << fut.get() << std::endl;
    t.join();
}

void PromiseExceptionDemo::Run() {
    std::cout << "\n=== Promise Exception Demo ===" << std::endl;
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();
    std::thread t([&prom]() {
        try {
            throw std::runtime_error("Something went wrong");
        } catch (...) {
            prom.set_exception(std::current_exception());
        }
    });
    try {
        int value = fut.get();
        std::cout << "Should not print: " << value << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    t.join();
}

void DeferredDemo::Run() {
    std::cout << "\n=== Deferred Launch Demo ===" << std::endl;
    auto lazy = std::async(std::launch::deferred, [] {
        std::cout << "Deferred task starting now\n";
        return 55;
    });
    std::cout << "Nothing runs until get()...\n";
    int val = lazy.get();
    std::cout << "Deferred result = " << val << std::endl;
}

}  // namespace future_demo
