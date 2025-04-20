#ifndef BOOST_CORE_EXAMPLES_HPP
#define BOOST_CORE_EXAMPLES_HPP

// Boost Smart Pointers
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

// Boost Threading & Synchronization
#include <boost/thread.hpp>
#include <boost/thread/latch.hpp>
#include <boost/thread/barrier.hpp>
#include <boost/thread/condition_variable.hpp>

// Boost Filesystem & Regex
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

// Boost Asynchronous I/O
#include <boost/asio.hpp>
#include <boost/asio/thread_pool.hpp>

// Boost Program Options & Serialization
#include <boost/program_options.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

// Boost Coroutine & Lockfree
#include <boost/coroutine2/coroutine.hpp>
#include <boost/lockfree/queue.hpp>

// Boost Interprocess Communication
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include <atomic>
#include <chrono>
#include <functional>
#include <thread>
#include <future>
#include <vector>
#include <queue>

class BoostCoreExamples {
public:
    BoostCoreExamples();

    // Demonstrates usage of boost::shared_ptr for shared ownership.
    void sharedPtrExample();

    // Demonstrates usage of boost::scoped_ptr for exclusive ownership.
    void scopedPtrExample();

    // Demonstrates basic operations using boost::filesystem (e.g., current_path, create_directory).
    void filesystemExample();

    // Demonstrates boost::regex for pattern matching.
    void regexExample();

    // Demonstrates high-concurrency task execution using std::thread and std::future.
    void threadExample();

    // Demonstrates task scheduling using boost::asio::thread_pool.
    void threadPoolExample();

    // Demonstrates async task dispatching with boost::asio::io_context and thread pool.
    void asyncCalculationExample();

    // Demonstrates command-line option parsing using boost::program_options.
    void programOptionsExample();

    // Demonstrates object serialization and deserialization using boost::archive.
    void serializationExample();

    // Demonstrates boost::coroutine2 to yield control and simulate generator behavior.
    void coroutineExample();

    // Demonstrates boost::interprocess shared memory creation and access.
    void interprocessExample();

    // Demonstrates lock-free concurrent queue using boost::lockfree::queue.
    void lockfreeExample();

    // Demonstrates basic TCP socket connection using boost::asio.
    void asioSocketExample();

    // Demonstrates directory traversal using boost::filesystem::directory_iterator.
    void filesystemTraverseExample();

    // Demonstrates regex replacement using boost::regex_replace.
    void regexReplaceExample();

    // Demonstrates multi-threading using boost::thread and joining threads.
    void boostThreadExample();

    // Demonstrates thread barrier synchronization
    void barrierExample();

    // Demonstrates thread latch synchronization
    void latchExample();

    // Demonstrates producer-consumer using boost::condition_variable
    void conditionVariableExample();

private:
    // Simulates a simple computation with artificial delay.
    int simple_calculation(int task_id);

    // Simulates a CPU-intensive task to test parallel performance.
    int complex_calculation(int task_id);

    // Task executed by threads for benchmarking.
    void executeTask(int task_id, std::atomic<int>& completed_tasks);
};

#endif // BOOST_CORE_EXAMPLES_HPP
