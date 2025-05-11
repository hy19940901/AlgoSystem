#ifndef CPP20_THREAD_H
#define CPP20_THREAD_H

#include <thread>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <vector>
#include <queue>
#include <atomic>
#include <barrier>
#include <semaphore>
#include <chrono>
#include <future>
#include <stdexcept>
#include <cmath>
#include <random>

// ======================= Thread API Declarations =======================
// std::thread represents a unit of execution. You use it when:
// - You want full control over thread lifetime.
// - You manage shared data and synchronization manually.
// - You need fire-and-forget or precise scheduling.
// 
// Avoid std::thread directly if:
// - You need return values (prefer future/async).
// - You want exception-safe structured concurrency.
namespace thread_demo {

/**
 * @brief Demonstrates basic thread creation and joining.
 * 
 * Use when you need to understand how threads are launched and synchronized via join().
 * Pros: Simple and direct.
 * Cons: Manual synchronization and error handling required.
 */
class BasicThreadsDemo {
public:
    static void Run();
};

/**
 * @brief Demonstrates detached thread usage.
 * 
 * Use when threads should continue running independently (fire-and-forget).
 * Pros: No need to join.
 * Cons: Difficult to manage lifecycle or handle errors.
 */
class DetachedThreadsDemo {
public:
    static void Run();
};

/**
 * @brief Demonstrates mutex for protecting shared data.
 * 
 * Use when multiple threads need synchronized access to shared resources.
 * Pros: Guarantees exclusive access.
 * Cons: Risk of deadlock, lower performance than lock-free.
 */
class MutexDemo {
public:
    void Run();

private:
    void Worker();
    int counter_ = 0;
    std::mutex mutex_;
};

/**
 * @brief Demonstrates condition_variable for signaling between threads.
 * 
 * Use when one or more threads must wait for a condition.
 * Pros: Efficient waiting.
 * Cons: Requires careful predicate and locking logic.
 */
class ConditionDemo {
public:
    void Run();

private:
    std::mutex mutex_;
    std::condition_variable cv_;
    bool ready_ = false;
    void Waiter();
};

/**
 * @brief Demonstrates read/write synchronization using shared_mutex.
 * 
 * Use when many readers but few writers access a shared resource.
 * Pros: Readers don't block each other.
 * Cons: Writers must wait for all readers to finish.
 */
class RwlockDemo {
public:
    void Run();

private:
    std::shared_mutex rw_mutex_;
    int shared_data_ = 0;
    void ReaderTask(int id);
    void WriterTask();
};

/**
 * @brief Demonstrates barrier synchronization across threads.
 * 
 * Use when multiple threads must reach the same point before continuing.
 * Pros: Simple group synchronization.
 * Cons: All threads must participate correctly.
 */
class BarrierDemo {
public:
    void Run();

private:
    std::barrier<> sync_point_{3};
    void Task(int id);
};

/**
 * @brief Demonstrates thread-local storage using thread_local.
 * 
 * Use when each thread needs its own copy of a variable.
 * Pros: No need for locks.
 * Cons: Memory use scales with threads.
 */
class TlsDemo {
public:
    void Run();

private:
    static thread_local int tls_var_;
    void Task(int id);
};

/**
 * @brief Demonstrates a simple spinlock using atomic_flag.
 * 
 * Use for very short critical sections with low contention.
 * Pros: Fast under light load.
 * Cons: Wastes CPU cycles under contention.
 */
class SpinlockDemo {
public:
    void Run();

private:
    std::atomic_flag spinlock_ = ATOMIC_FLAG_INIT;
    int counter_ = 0;
    void Worker();
};

/**
 * @brief Demonstrates semaphore to limit concurrency.
 * 
 * Use to control access to a fixed-size pool of resources.
 * Pros: Efficient for throttling concurrent accesses.
 * Cons: Can be harder to debug than mutex.
 */
class SemaphoreDemo {
public:
    void Run();

private:
    std::counting_semaphore<3> sem_{2};
    int counter_ = 0;
    void Worker(int id);
};

/**
 * @brief Demonstrates the producer-consumer pattern.
 * 
 * Use for decoupling data production and consumption.
 * Pros: Common concurrency pattern; efficient with condition_variable.
 * Cons: Requires careful buffer and lock handling.
 */
class ProducerConsumerDemo {
public:
    void Run();

private:
    std::queue<int> buffer_;
    std::mutex mutex_;
    std::condition_variable cv_;
    const int kMaxBuffer = 5;
    bool done_ = false;
    void Producer();
    void Consumer(int id);
};

/**
 * @brief Demonstrates thread cancellation using atomic flag.
 * 
 * Use when threads should terminate based on external signal.
 * Pros: Simple and safe.
 * Cons: Cooperative — threads must check the flag.
 */
class CancellationDemo {
public:
    void Run();

private:
    std::atomic<bool> cancel_flag_{false};
    void Worker();
};

/**
 * @brief Compares performance of mutex, atomic, and single-threaded increments.
 * 
 * Use to understand the overhead of different synchronization techniques.
 * Pros: Reveals tradeoffs.
 */
class ThreadBenchmarkDemo {
public:
    void Run();
};

/**
 * @brief Compares serial and parallel execution of a heavy task.
 * 
 * Use to demonstrate speedup from multithreading.
 * Pros: Shows effect of parallelism.
 */
class ParallelVsSerialDemo {
public:
    void Run();
};

}

// ======================= Future & Async API =======================
// std::future is a synchronization primitive that allows:
// - Retrieving return value from a background task.
// - Managing exceptions thrown in asynchronous tasks.
// - Synchronizing computation (blocking with get/wait/wait_for).
// 
// Use std::future when:
// - You need a result from a function running in another thread.
// - You want to run background tasks with exception handling.
// - You use std::async or std::packaged_task.
// 
// Avoid std::future if:
// - You need shared results (use shared_future).
// - You want to cancel a long-running task (use atomic flag or jthread).
// - You need repeated use (futures are move-only and single-use).
namespace future_demo {

/**
 * @brief Demonstrates std::future and std::async.
 * 
 * Use for launching background tasks and retrieving results.
 * Pros: Simple and type-safe.
 */
class FutureDemo {
public:
    static void Run();
};

/**
 * @brief Demonstrates std::packaged_task.
 * 
 * Use for wrapping callable objects and executing in threads.
 * Pros: Useful for custom scheduling or thread pools.
 */
class PackagedTaskDemo {
public:
    static void Run();
};

/**
 * @brief Demonstrates std::shared_future.
 * 
 * Use when multiple threads need to access the same result.
 * Pros: Efficient sharing of results.
 */
class SharedFutureDemo {
public:
    static void Run();
};

/**
 * @brief Demonstrates timeout using future::wait_for().
 * 
 * Use when you want to wait but only for a limited time.
 */
class WaitForDemo {
public:
    static void Run();
};

/**
 * @brief Demonstrates value transfer between threads using std::promise.
 * 
 * Use when one thread produces a value to be consumed by another.
 */
class PromiseDemo {
public:
    static void Run();
};

/**
 * @brief Demonstrates exception passing using promise and future.
 * 
 * Use when producer might fail and consumer must be notified.
 */
class PromiseExceptionDemo {
public:
    static void Run();
};

/**
 * @brief Demonstrates deferred execution via std::launch::deferred.
 * 
 * Use when lazy evaluation is needed.
 * Pros: Executes only if get() is called.
 */
class DeferredDemo {
public:
    static void Run();
};

}  // namespace future_demo

#endif // CPP20_THREAD_H
