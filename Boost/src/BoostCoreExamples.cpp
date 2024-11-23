#include "../include/BoostCoreExamples.hpp"
#include <iostream>

const int num_tasks = 10000; 

// Constructor
BoostCoreExamples::BoostCoreExamples() {}

// Shared Pointer Example
void BoostCoreExamples::sharedPtrExample() {
    boost::shared_ptr<int> ptr1(new int(10));
    boost::shared_ptr<int> ptr2 = ptr1; // Both pointers share ownership
    std::cout << "Shared Pointer Value: " << *ptr1 << std::endl;
    std::cout << "Shared Pointer Use Count: " << ptr1.use_count() << std::endl;
}

// Scoped Pointer Example
void BoostCoreExamples::scopedPtrExample() {
    boost::scoped_ptr<int> ptr(new int(20));
    std::cout << "Scoped Pointer Value: " << *ptr << std::endl;
    // No need to manually delete; scoped_ptr takes care of it
}

// Filesystem Example
void BoostCoreExamples::filesystemExample() {
    boost::filesystem::path path = boost::filesystem::current_path();
    std::cout << "Current Path: " << path << std::endl;
    // Create a new directory for demonstration
    boost::filesystem::create_directory("example_dir");
}

// Regex Example
void BoostCoreExamples::regexExample() {
    std::string text = "Boost Libraries";
    boost::regex pattern("(\\w+)\\s(\\w+)");
    boost::smatch result;
    if (boost::regex_search(text, result, pattern)) {
        std::cout << "Matched: " << result[0] << std::endl;
    }
}

// Thread Example (Standard C++ Threads and std::future)
void BoostCoreExamples::threadExample() {
    std::vector<std::future<void>> futures;  // 更改为存储 std::future<void>
    std::atomic<int> completed_tasks(0);  // 用于跟踪已完成任务数

    auto start_time = std::chrono::steady_clock::now();

    // 启动 num_tasks 个任务，每个任务在新线程中运行，并在任务完成后销毁线程
    for (int i = 0; i < num_tasks; ++i) {
        // 使用 std::async 异步运行 executeTask，并传递参数
        futures.push_back(std::async(std::launch::async, &BoostCoreExamples::executeTask, this, i, std::ref(completed_tasks)));
    }

    // 等待所有任务完成，并处理结果
    for (auto& fut : futures) {
        try {
            fut.get();  // 等待每个任务完成
        } catch (const std::exception& e) {
            std::cerr << "Task encountered an error: " << e.what() << "\n";
        }
    }

    auto end_time = std::chrono::steady_clock::now();
    auto total_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "Task with Thread. All tasks completed. Total time: " << total_duration << "ms\n";
}

// 使用线程池的任务执行
void BoostCoreExamples::threadPoolExample() {
    unsigned int thread_count = std::thread::hardware_concurrency() * 2;  // 根据CPU核心数设置线程数
    
    std::cout << "Thread pool size: " << thread_count << " threads.\n";

    // 创建 Boost 线程池
    boost::asio::thread_pool pool(thread_count);

    std::atomic<int> completed_tasks(0);

    auto start_time = std::chrono::steady_clock::now();

    // 启动 num_tasks 个任务
    for (int i = 0; i < num_tasks; ++i) {
        boost::asio::post(pool, std::bind(&BoostCoreExamples::executeTask, this, i, std::ref(completed_tasks)));
    }

    // 等待任务完成
    while (completed_tasks < num_tasks) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));  // 简单轮询等待
    }

    // 等待线程池中的所有任务完成
    pool.join();

    auto end_time = std::chrono::steady_clock::now();
    auto total_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "Task with Thread Pool. All tasks completed. Total time: " << total_duration << "ms\n";
}

// Asynchronous Calculation Example
void BoostCoreExamples::asyncCalculationExample() {
    
    // 获取系统支持的并发线程数
    unsigned int thread_count = std::thread::hardware_concurrency() * 2;
    std::cout << "Thread pool size: " << thread_count << " threads.\n";
    
    // 创建 io_context 和线程池
    boost::asio::io_context io_context;
    boost::asio::thread_pool pool(thread_count);  // 根据系统硬件核心数创建线程池
    std::atomic<int> completed_tasks(0);

    // 记录开始时间
    auto start_time = std::chrono::steady_clock::now();

    // 启动 100 个异步计算任务
    for (int i = 0; i < num_tasks; ++i) {
        boost::asio::post(pool, std::bind(&BoostCoreExamples::executeTask, this, i, std::ref(completed_tasks)));
    }

    // 运行 io_context 来处理异步任务
    std::thread io_context_thread([&io_context]() {
        io_context.run();
    });

    // 等待所有任务完成
    while (completed_tasks < num_tasks) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));  // 简单轮询等待
    }

    // 记录结束时间
    auto end_time = std::chrono::steady_clock::now();
    auto total_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "Task with Asynchronous and Threadpool. All tasks completed. Total time: " << total_duration << "ms\n";

    // 停止 io_context 线程池
    io_context.stop();
    io_context_thread.join();
    pool.join();
}

// 将 lambda 表达式提取为独立的成员函数
void BoostCoreExamples::executeTask(int task_id, std::atomic<int>& completed_tasks) {
    //int result = this->simple_calculation(task_id);
    int result = this->complex_calculation(task_id);
    //std::cout << "Task " << task_id << " completed, result: " << result << "\n";
    completed_tasks++;
}

// 模拟一个计算任务，返回 task_id，并模拟耗时 100ms
int BoostCoreExamples::simple_calculation(int task_id) {
    // 模拟耗时 100ms
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return task_id;  // 返回 task_id
}

int BoostCoreExamples::complex_calculation(int task_id) {
    // 模拟较复杂的计算
    if (task_id == 0) {
        return 0;
    }
    int result = 0;
    for (int i = 0; i < 1000000; ++i) {
        result += i % task_id + 1;  // 一些简单的计算来占用 CPU
    }
    return result;  // 返回计算结果
}