#include <boost/asio.hpp>
#include <iostream>
#include <pthread.h>
#include <thread>
#include <chrono>
#include <vector>
#include <queue>
#include <cstdlib>   // For rand and srand
#include <ctime>     // For time
#include <functional> // For std::function in C++11
#include <atomic>    // For atomic variables in C++11
#include <mutex>     // For std::mutex
#include <condition_variable> // For std::condition_variable

// Define callback function pointers for C++03
typedef void (*computation_callback)(const std::string&, double);

// Polling interval in seconds
const int k_polling_interval = 3;

// Shared state for synchronization
std::mutex mtx;
std::condition_variable cv;
bool task_completed = false;  // Indicates if a task has been completed

// Task queue for storing callbacks and their parameters
std::queue<std::pair<std::string, double>> task_queue;
std::mutex queue_mutex;
std::condition_variable queue_cv;
bool stop_callback_thread = false;  // To stop the callback processing thread

boost::asio::io_service io_service;  // Boost Asio I/O service

// Callback processing function
void callback_processor() {
    while (true) {
        std::unique_lock<std::mutex> lock(queue_mutex);
        queue_cv.wait(lock, [] { return !task_queue.empty() || stop_callback_thread; });

        if (stop_callback_thread && task_queue.empty()) {
            break;  // Exit the loop if stop flag is set and queue is empty
        }

        // Process the callback
        auto task = task_queue.front();
        task_queue.pop();
        lock.unlock();

        // Execute the callback
        std::cout << "\n[Callback Processor] Thread ID: " << std::this_thread::get_id()
                  << " [Callback] " << task.first << ". Time taken: " << task.second << " seconds."
                  << std::endl;
    }
}

// C++03: Perform a complex task using Boost timer
void perform_complex_task_cpp03(boost::asio::steady_timer* timer) {
    std::cout << "\n[C++03] perform_complex_task Thread ID: " << pthread_self() << std::endl;

    // Simulate a complex task
    std::vector<int> data(10000000);
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] = rand();  // Fill with random data
    }

    // Measure the start time
    std::clock_t start = std::clock();

    // Simulate writing to a file (write data to a memory buffer instead)
    std::string simulated_file;
    for (size_t i = 0; i < data.size(); ++i) {
        simulated_file += std::to_string(data[i]) + "\n";
    }

    // Simulate more processing delay
    for (size_t i = 0; i < 10000000; ++i) {
        simulated_file[i % simulated_file.size()] =
            (simulated_file[i % simulated_file.size()] + 1) % 256;
    }

    // Measure the end time
    double elapsed = double(std::clock() - start) / CLOCKS_PER_SEC;

    // Add the callback task to the queue
    {
        std::lock_guard<std::mutex> lock(queue_mutex);
        task_queue.push({"C++03 task completed", elapsed});
    }
    queue_cv.notify_one();

    // Reset the timer for the next iteration
    timer->expires_after(std::chrono::seconds(k_polling_interval));
    timer->async_wait([timer](const boost::system::error_code&) {
        perform_complex_task_cpp03(timer);
    });
}

// Modern C++ (C++11 and above): Perform a complex task using Boost timer
void perform_complex_task_modern_cpp(boost::asio::steady_timer* timer, std::atomic<bool>& stop_flag) {
    if (stop_flag) {
        return;  // Stop if the flag is set
    }

    std::cout << "\n[C++11] perform_complex_task Thread ID: " << std::this_thread::get_id() << std::endl;

    // Measure the start time
    auto start = std::chrono::high_resolution_clock::now();

    // Simulate a complex task
    std::vector<int> data(10000000);
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] = rand();  // Fill with random data
    }

    // Simulate writing to a file (write data to a memory buffer instead)
    std::string simulated_file;
    for (size_t i = 0; i < data.size(); ++i) {
        simulated_file += std::to_string(data[i]) + "\n";
    }

    // Simulate more processing delay
    for (size_t i = 0; i < 10000000; ++i) {
        simulated_file[i % simulated_file.size()] =
            (simulated_file[i % simulated_file.size()] + 1) % 256;
    }

    // Measure the end time
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Add the callback task to the queue
    {
        std::lock_guard<std::mutex> lock(queue_mutex);
        task_queue.push({"C++11 task completed", elapsed.count()});
    }
    queue_cv.notify_one();

    // Reset the timer for the next iteration
    timer->expires_after(std::chrono::seconds(k_polling_interval));
    timer->async_wait([timer, &stop_flag](const boost::system::error_code&) {
        perform_complex_task_modern_cpp(timer, stop_flag);
    });
}

int main() {
    srand(time(0));  // Seed random number generator

    // Start the callback processing thread
    std::thread callback_thread(callback_processor);

    // C++03: Using Boost.Asio timer
    boost::asio::steady_timer timer_cpp03(io_service, std::chrono::seconds(k_polling_interval));
    timer_cpp03.async_wait([&timer_cpp03](const boost::system::error_code&) {
        perform_complex_task_cpp03(&timer_cpp03);
    });

    // Modern C++: Using Boost.Asio timer with stop flag
    std::atomic<bool> stop_flag(false);
    boost::asio::steady_timer timer_cpp11(io_service, std::chrono::seconds(k_polling_interval));
    timer_cpp11.async_wait([&timer_cpp11, &stop_flag](const boost::system::error_code&) {
        perform_complex_task_modern_cpp(&timer_cpp11, stop_flag);
    });

    // Run the I/O service in a separate thread
    std::thread io_thread([]() { io_service.run(); });

    // Main thread logging
    for (int i = 0; i < 10; ++i) {
        std::cout << "\n[Main Thread] Main thread ID: " << std::this_thread::get_id()
                  << " [Main Thread] Main thread is running..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Stop the C++11 polling system
    stop_flag = true;

    // Stop the callback processing thread
    {
        std::lock_guard<std::mutex> lock(queue_mutex);
        stop_callback_thread = true;
    }
    queue_cv.notify_one();

    // Stop the I/O service and join threads
    io_service.stop();
    if (callback_thread.joinable()) {
        callback_thread.join();
    }
    if (io_thread.joinable()) {
        io_thread.join();
    }

    std::cout << "\nPolling systems stopped." << std::endl;
    return 0;
}
