#include "../include/FixedThreadPool.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <future>
#include <atomic>
#include <thread>

constexpr int TASK_COUNT = 100000;

void benchmark_thread_pool() {
    FixedThreadPool pool(8);
    std::atomic<int> counter{0};
    std::vector<std::future<void>> results;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < TASK_COUNT; ++i) {
        results.emplace_back(pool.submit([&counter]() {
            counter.fetch_add(1, std::memory_order_relaxed);
        }));
    }

    for (auto& f : results) f.get();

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "[ThreadPool] Time taken: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms, counter = " << counter << "\n";
}

void benchmark_direct_threads() {
    std::atomic<int> counter{0};
    std::vector<std::thread> threads;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < TASK_COUNT; ++i) {
        threads.emplace_back([&counter]() {
            counter.fetch_add(1, std::memory_order_relaxed);
        });
    }

    for (auto& t : threads) t.join();

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "[DirectThreads] Time taken: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms, counter = " << counter << "\n";
}

int main() {
    std::cout << "Running benchmark with TASK_COUNT = " << TASK_COUNT << "\n";

    benchmark_thread_pool();
    benchmark_direct_threads();

    return 0;
}
