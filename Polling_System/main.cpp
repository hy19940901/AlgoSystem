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
typedef void (*ComputationCallback)(const std::string&, double);

// Polling interval in seconds
const int POLLING_INTERVAL = 3;

// Shared state for synchronization
std::mutex mtx;
std::condition_variable cv;
bool taskCompleted = false; // Indicates if a task has been completed

// Task queue for storing callbacks and their parameters
std::queue<std::pair<std::string, double>> taskQueue;
std::mutex queueMutex;
std::condition_variable queueCV;
bool stopCallbackThread = false; // To stop the callback processing thread

boost::asio::io_service io_service; // Boost Asio I/O service

// Callback processing function
void callbackProcessor() {
    while (true) {
        std::unique_lock<std::mutex> lock(queueMutex);
        queueCV.wait(lock, [] { return !taskQueue.empty() || stopCallbackThread; });

        if (stopCallbackThread && taskQueue.empty()) {
            break; // Exit the loop if stop flag is set and queue is empty
        }

        // Process the callback
        auto task = taskQueue.front();
        taskQueue.pop();
        lock.unlock();

        // Execute the callback
        std::cout << "\n[Callback Processor] Thread ID: " << std::this_thread::get_id() << " [Callback] " << task.first << ". Time taken: " << task.second << " seconds." << std::endl;
    }
}

// C++03: Perform a complex task using Boost timer
void performComplexTaskCpp03(boost::asio::steady_timer* timer) {
    std::cout << "\n[C++03] performComplexTask Thread ID: " << pthread_self() << std::endl;
    
    // Simulate a complex task
    std::vector<int> data(10000000);
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] = rand(); // Fill with random data
    }

    // Measure the start time
    std::clock_t start = std::clock();

    // Simulate writing to a file (write data to a memory buffer instead)
    std::string simulatedFile;
    for (size_t i = 0; i < data.size(); ++i) {
        simulatedFile += std::to_string(data[i]) + "\n";
    }

    // Simulate more processing delay
    for (size_t i = 0; i < 10000000; ++i) {
        simulatedFile[i % simulatedFile.size()] = (simulatedFile[i % simulatedFile.size()] + 1) % 256;
    }

    // Measure the end time
    double elapsed = double(std::clock() - start) / CLOCKS_PER_SEC;

    // Add the callback task to the queue
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        taskQueue.push({"C++03 task completed", elapsed});
    }
    queueCV.notify_one();

    // Reset the timer for the next iteration
    timer->expires_after(std::chrono::seconds(POLLING_INTERVAL));
    timer->async_wait([timer](const boost::system::error_code&) {
        performComplexTaskCpp03(timer);
    });
}

// Modern C++ (C++11 and above): Perform a complex task using Boost timer
void performComplexTaskModernCpp(boost::asio::steady_timer* timer, std::atomic<bool>& stopFlag) {
    if (stopFlag) {
        return; // Stop if the flag is set
    }

    std::cout << "\n[C++11] performComplexTask Thread ID: " << std::this_thread::get_id() << std::endl;

    // Measure the start time
    auto start = std::chrono::high_resolution_clock::now();

    // Simulate a complex task
    std::vector<int> data(10000000);
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] = rand(); // Fill with random data
    }

    // Simulate writing to a file (write data to a memory buffer instead)
    std::string simulatedFile;
    for (size_t i = 0; i < data.size(); ++i) {
        simulatedFile += std::to_string(data[i]) + "\n";
    }

    // Simulate more processing delay
    for (size_t i = 0; i < 10000000; ++i) {
        simulatedFile[i % simulatedFile.size()] = (simulatedFile[i % simulatedFile.size()] + 1) % 256;
    }

    // Measure the end time
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Add the callback task to the queue
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        taskQueue.push({"C++11 task completed", elapsed.count()});
    }
    queueCV.notify_one();

    // Reset the timer for the next iteration
    timer->expires_after(std::chrono::seconds(POLLING_INTERVAL));
    timer->async_wait([timer, &stopFlag](const boost::system::error_code&) {
        performComplexTaskModernCpp(timer, stopFlag);
    });
}

int main() {
    srand(time(0)); // Seed random number generator

    // Start the callback processing thread
    std::thread callbackThread(callbackProcessor);

    // C++03: Using Boost.Asio timer
    boost::asio::steady_timer timerCpp03(io_service, std::chrono::seconds(POLLING_INTERVAL));
    timerCpp03.async_wait([&timerCpp03](const boost::system::error_code&) {
        performComplexTaskCpp03(&timerCpp03);
    });

    // Modern C++: Using Boost.Asio timer with stop flag
    std::atomic<bool> stopFlag(false);
    boost::asio::steady_timer timerCpp11(io_service, std::chrono::seconds(POLLING_INTERVAL));
    timerCpp11.async_wait([&timerCpp11, &stopFlag](const boost::system::error_code&) {
        performComplexTaskModernCpp(&timerCpp11, stopFlag);
    });

    // Run the I/O service in a separate thread
    std::thread ioThread([]() { io_service.run(); });

    // Main thread logging
    for (int i = 0; i < 10; ++i) {
        std::cout << "\n[Main Thread] Main thread ID: " << std::this_thread::get_id() << " [Main Thread] Main thread is running..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Stop the C++11 polling system
    stopFlag = true;

    // Stop the callback processing thread
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        stopCallbackThread = true;
    }
    queueCV.notify_one();

    // Stop the I/O service and join threads
    io_service.stop();
    if (callbackThread.joinable()) {
        callbackThread.join();
    }
    if (ioThread.joinable()) {
        ioThread.join();
    }

    std::cout << "\nPolling systems stopped." << std::endl;

    return 0;
}
