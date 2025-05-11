#ifndef BOOST_CORE_EXAMPLES_HPP
#define BOOST_CORE_EXAMPLES_HPP

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <boost/program_options.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/coroutine2/all.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/thread/barrier.hpp>
#include <boost/thread/latch.hpp>
#include <boost/thread/condition_variable.hpp>

#include <string>
#include <atomic>
#include <future>
#include <queue>

/**
 * @brief A class demonstrating various Boost library components and concurrency mechanisms.
 */
class BoostCoreExamples {
public:
    BoostCoreExamples();

    // === Smart Pointer Examples ===
    void shared_ptr_example();           // Demonstrates boost::shared_ptr usage
    void scoped_ptr_example();           // Demonstrates boost::scoped_ptr usage

    // === Filesystem and Regex ===
    void filesystem_example();           // Prints and creates current directory using boost::filesystem
    void regex_example();                // Performs regex search using boost::regex
    void regex_replace_example();        // Replaces text using boost::regex_replace
    void filesystem_traverse_example();  // Traverses current directory using boost::filesystem

    // === Threading and Task Execution ===
    void thread_example();               // Launches many std::async threads to run tasks
    void thread_pool_example();          // Uses boost::asio::thread_pool to run tasks
    void async_calculation_example();    // Async calculation with io_context and thread_pool

    // === Command Line / Serialization / Coroutine ===
    void program_options_example();      // Demonstrates boost::program_options
    void serialization_example();        // Demonstrates serialization with boost::archive
    void coroutine_example();            // Demonstrates coroutine using boost::coroutines2

    // === Interprocess & Lockfree Queue ===
    void interprocess_example();         // Demonstrates shared memory using boost::interprocess
    void lockfree_example();             // Demonstrates lock-free queue with boost::lockfree::queue

    // === Networking ===
    void asio_socket_example();          // Performs TCP connect using boost::asio

    // === Boost Threads ===
    void boost_thread_example();         // Launches multiple boost::thread and joins them
    void barrier_example();              // Demonstrates boost::barrier synchronization
    void latch_example();                // Demonstrates boost::latch synchronization
    void condition_variable_example();   // Demonstrates producer-consumer using boost::condition_variable

    // === Helper Methods ===
    void execute_task(int task_id, std::atomic<int>& completed_tasks);  // Executes task (called in pool/async)
    int simple_calculation(int task_id);     // Simulates a simple delay task
    int complex_calculation(int task_id);    // Simulates a CPU-intensive task
};

#endif // BOOST_CORE_EXAMPLES_HPP
