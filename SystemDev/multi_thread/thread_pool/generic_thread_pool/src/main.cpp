#include "../include/generic_thread_pool.hpp"
#include <iostream>
#include <chrono>
#include <vector>
#include <future>
#include <atomic>
#include <thread>

constexpr int TASK_COUNT = 100000;

void BenchmarkThreadPool() {
    ThreadPool pool(8);
    std::atomic<int> counter{0};

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::future<void>> futures;
    for (int i = 0; i < TASK_COUNT; ++i) {
        futures.emplace_back(pool.submit([&counter]() {
            counter.fetch_add(1, std::memory_order_relaxed);
        }));
    }

    for (auto& fut : futures)
        fut.get();

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "[ThreadPool] Time taken: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms, counter = " << counter << "\n";
}

void BenchmarkStdAsync() {
    std::atomic<int> counter{0};

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::future<void>> futures;
    for (int i = 0; i < TASK_COUNT; ++i) {
        futures.emplace_back(std::async(std::launch::async, [&counter]() {
            counter.fetch_add(1, std::memory_order_relaxed);
        }));
    }

    for (auto& fut : futures)
        fut.get();

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "[std::async] Time taken: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms, counter = " << counter << "\n";
}

void BenchmarkSingleThread() {
    int counter = 0;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < TASK_COUNT; ++i) {
        counter++;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "[SingleThread] Time taken: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms, counter = " << counter << "\n";
}

int main() {
    std::cout << "Benchmark started with TASK_COUNT = " << TASK_COUNT << "\n";

    BenchmarkThreadPool();
    BenchmarkStdAsync();
    BenchmarkSingleThread();

    return 0;
}
