#include "../include/ThreadPool.h"
#include <iostream>
#include <chrono>
#include <future>
#include <vector>

/**
 * @brief Simulates a time-consuming task.
 * @param n Task identifier.
 */
void heavyTask(int n) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "Task " << n << " completed." << std::endl;
}

/**
 * @brief Callback function to handle task completion.
 * @param result The result passed from the completed task.
 */
void taskCallback(int result) {
    std::cout << "Callback: Task completed with result = " << result << std::endl;
}

/**
 * @brief Executes tasks synchronously.
 */
void executeSync() {
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 10; ++i) {
        heavyTask(i);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Sync execution time: " << elapsed.count() << " seconds." << std::endl;
}

/**
 * @brief Executes tasks asynchronously using a thread pool.
 */
void executeWithThreadPool() {
    ThreadPool pool(10);  // Create a thread pool with 10 threads

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::future<void>> results;

    for (int i = 0; i < 10; ++i) {
        results.push_back(pool.enqueue([i] { heavyTask(i); }, taskCallback));
    }

    for (auto& result : results) {
        result.get();  // Wait for all tasks to complete
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Execution time with ThreadPool: " << elapsed.count() << " seconds." << std::endl;
}

/**
 * @brief Executes tasks using multiple threads without a thread pool.
 */
void executeWithThreads() {
    std::vector<std::thread> threads;
    auto start = std::chrono::high_resolution_clock::now();

    // Create multiple threads to execute tasks
    for (int i = 0; i < 10; ++i) {
        threads.push_back(std::thread([i] { heavyTask(i); }));
    }

    // Wait for all threads to complete
    for (auto& t : threads) {
        t.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Execution time with multiple threads (without thread pool): " << elapsed.count() << " seconds." << std::endl;
}

int main() {
    std::cout << "Starting sync execution..." << std::endl;
    executeSync();

    std::cout << "\nStarting async execution with thread pool..." << std::endl;
    executeWithThreadPool();

    std::cout << "\nStarting async execution with threads only..." << std::endl;
    executeWithThreads();

    return 0;
}
