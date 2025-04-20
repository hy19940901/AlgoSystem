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
    // No need to manually delete; scoped_ptr handles it automatically
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
    std::vector<std::future<void>> futures;  // Store std::future<void>
    std::atomic<int> completed_tasks(0);     // Track number of completed tasks

    auto start_time = std::chrono::steady_clock::now();

    // Launch num_tasks tasks, each in a new thread, automatically destroyed after completion
    for (int i = 0; i < num_tasks; ++i) {
        futures.push_back(std::async(std::launch::async, &BoostCoreExamples::executeTask, this, i, std::ref(completed_tasks)));
    }

    // Wait for all tasks to complete
    for (auto& fut : futures) {
        try {
            fut.get();  // Wait for each task to finish
        } catch (const std::exception& e) {
            std::cerr << "Task encountered an error: " << e.what() << "\n";
        }
    }

    auto end_time = std::chrono::steady_clock::now();
    auto total_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "Task with Thread. All tasks completed. Total time: " << total_duration << "ms\n";
}

// Task execution using thread pool
void BoostCoreExamples::threadPoolExample() {
    unsigned int thread_count = std::thread::hardware_concurrency() * 2;  // Use 2x number of hardware threads

    std::cout << "Thread pool size: " << thread_count << " threads.\n";

    // Create Boost thread pool
    boost::asio::thread_pool pool(thread_count);

    std::atomic<int> completed_tasks(0);

    auto start_time = std::chrono::steady_clock::now();

    // Launch num_tasks tasks
    for (int i = 0; i < num_tasks; ++i) {
        boost::asio::post(pool, std::bind(&BoostCoreExamples::executeTask, this, i, std::ref(completed_tasks)));
    }

    // Wait until all tasks are completed
    while (completed_tasks < num_tasks) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));  // Simple polling
    }

    // Wait for all tasks in thread pool to complete
    pool.join();

    auto end_time = std::chrono::steady_clock::now();
    auto total_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "Task with Thread Pool. All tasks completed. Total time: " << total_duration << "ms\n";
}

// Asynchronous Calculation Example
void BoostCoreExamples::asyncCalculationExample() {
    unsigned int thread_count = std::thread::hardware_concurrency() * 2;
    std::cout << "Thread pool size: " << thread_count << " threads.\n";

    boost::asio::io_context io_context;
    boost::asio::thread_pool pool(thread_count);  // Create thread pool based on hardware concurrency
    std::atomic<int> completed_tasks(0);

    auto start_time = std::chrono::steady_clock::now();

    // Launch num_tasks asynchronous tasks
    for (int i = 0; i < num_tasks; ++i) {
        boost::asio::post(pool, std::bind(&BoostCoreExamples::executeTask, this, i, std::ref(completed_tasks)));
    }

    // Start io_context in a separate thread
    std::thread io_context_thread([&io_context]() {
        io_context.run();
    });

    // Wait until all tasks are completed
    while (completed_tasks < num_tasks) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));  // Simple polling
    }

    auto end_time = std::chrono::steady_clock::now();
    auto total_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "Task with Asynchronous and Threadpool. All tasks completed. Total time: " << total_duration << "ms\n";

    // Stop io_context and wait for the thread pool to finish
    io_context.stop();
    io_context_thread.join();
    pool.join();
}

// Extracted lambda expression as a member function
void BoostCoreExamples::executeTask(int task_id, std::atomic<int>& completed_tasks) {
    //int result = this->simple_calculation(task_id);
    int result = this->complex_calculation(task_id);
    //std::cout << "Task " << task_id << " completed, result: " << result << "\n";
    completed_tasks++;
}

// Simulate a task that returns task_id after a delay of 100ms
int BoostCoreExamples::simple_calculation(int task_id) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return task_id;
}

// Simulate a more complex CPU-intensive task
int BoostCoreExamples::complex_calculation(int task_id) {
    if (task_id == 0) {
        return 0;
    }
    int result = 0;
    for (int i = 0; i < 1000000; ++i) {
        result += i % task_id + 1;  // Simple CPU work
    }
    return result;
}

void BoostCoreExamples::programOptionsExample() {
    int age;
    std::string name;

    const char* argv[] = {"program", "--name=Boost", "--age=20"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("name", boost::program_options::value<std::string>(&name)->default_value("Unknown"), "User name")
        ("age", boost::program_options::value<int>(&age)->default_value(0), "User age");

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);

    std::cout << "Name: " << name << ", Age: " << age << std::endl;
}

void BoostCoreExamples::serializationExample() {
    std::ostringstream oss;
    {
        boost::archive::text_oarchive oa(oss);
        int x = 42;
        oa << x;
    }

    std::istringstream iss(oss.str());
    {
        boost::archive::text_iarchive ia(iss);
        int y = 0;
        ia >> y;
        std::cout << "Deserialized value: " << y << std::endl;
    }
}

void BoostCoreExamples::coroutineExample() {
    typedef boost::coroutines2::coroutine<int> coro_t;

    coro_t::pull_type source([&](coro_t::push_type& sink) {
        for (int i = 0; i < 5; ++i) {
            sink(i * i);
        }
    });

    for (auto val : source) {
        std::cout << "Coroutine value: " << val << std::endl;
    }
}

void BoostCoreExamples::interprocessExample() {
    using namespace boost::interprocess;

    const char* shm_name = "MySharedMemory";
    shared_memory_object::remove(shm_name);

    shared_memory_object shm(create_only, shm_name, read_write);
    shm.truncate(1024);

    mapped_region region(shm, read_write);
    std::memset(region.get_address(), 1, region.get_size());

    std::cout << "Shared memory created and initialized.\n";

    shared_memory_object::remove(shm_name);  // Clean up
}

void BoostCoreExamples::lockfreeExample() {
    boost::lockfree::queue<int> q(1024);

    for (int i = 0; i < 10; ++i) {
        q.push(i);
    }

    int value;
    while (q.pop(value)) {
        std::cout << "Popped: " << value << std::endl;
    }
}

void BoostCoreExamples::asioSocketExample() {
    using namespace boost::asio;
    io_context io;

    ip::tcp::resolver resolver(io);
    auto endpoints = resolver.resolve("example.com", "80");

    ip::tcp::socket socket(io);
    connect(socket, endpoints);

    std::cout << "Connected to example.com\n";
}

void BoostCoreExamples::filesystemTraverseExample() {
    boost::filesystem::path path = boost::filesystem::current_path();

    for (const auto& entry : boost::filesystem::directory_iterator(path)) {
        std::cout << entry.path().string() << std::endl;
    }
}

void BoostCoreExamples::regexReplaceExample() {
    std::string text = "Boost is amazing!";
    std::string replaced = boost::regex_replace(text, boost::regex("amazing"), "powerful");
    std::cout << "After replace: " << replaced << std::endl;
}

void BoostCoreExamples::boostThreadExample() {
    auto threadFunc = [](int id) {
        std::cout << "Thread " << id << " started\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "Thread " << id << " ended\n";
    };

    std::vector<boost::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(threadFunc, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "All Boost threads joined.\n";
}

void BoostCoreExamples::barrierExample() {
    boost::barrier sync_point(3);

    auto worker = [&](int id) {
        std::cout << "Thread " << id << " reached barrier\n";
        sync_point.wait();
        std::cout << "Thread " << id << " passed barrier\n";
    };

    boost::thread t1(worker, 1);
    boost::thread t2(worker, 2);
    boost::thread t3(worker, 3);
    t1.join(); t2.join(); t3.join();
}

void BoostCoreExamples::latchExample() {
    boost::latch sync_latch(3);

    auto task = [&](int id) {
        std::cout << "Thread " << id << " finished init\n";
        sync_latch.count_down();
        sync_latch.wait();
        std::cout << "Thread " << id << " proceeds\n";
    };

    boost::thread t1(task, 1);
    boost::thread t2(task, 2);
    boost::thread t3(task, 3);
    t1.join(); t2.join(); t3.join();
}

void BoostCoreExamples::conditionVariableExample() {
    std::queue<int> q;
    boost::mutex mutex;
    boost::condition_variable cond;
    bool done = false;

    auto producer = [&]() {
        for (int i = 0; i < 5; ++i) {
            boost::unique_lock<boost::mutex> lock(mutex);
            q.push(i);
            std::cout << "Produced: " << i << "\n";
            cond.notify_one();
        }
        boost::unique_lock<boost::mutex> lock(mutex);
        done = true;
        cond.notify_all();
    };

    auto consumer = [&]() {
        while (true) {
            boost::unique_lock<boost::mutex> lock(mutex);
            cond.wait(lock, [&] { return !q.empty() || done; });
            while (!q.empty()) {
                std::cout << "Consumed: " << q.front() << "\n";
                q.pop();
            }
            if (done) break;
        }
    };

    boost::thread prod(producer);
    boost::thread cons(consumer);
    prod.join(); cons.join();
}