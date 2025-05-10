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
    void run_basic_threads();
    void run_detached_threads_demo();
    void run_mutex_demo();
    void run_condition_demo();
    void run_rwlock_demo();
    void run_barrier_demo();
    void run_tls_demo();
    void run_spinlock_demo();
    void run_semaphore_demo();
    void run_producer_consumer_demo();
    void run_cancellation_demo();

    void run_thread_benchmark();
    void run_parallel_vs_serial_benchmark();
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

    // std::async with future.get()
    void run_future_demo();

    // std::packaged_task usage
    void run_packaged_task_demo();

    // std::shared_future shared between multiple consumers
    void run_shared_future_demo();

    // Demonstrates timeout waiting with future::wait_for()
    void run_wait_for_demo();

    // Demonstrates using std::promise to transfer data across threads
    void run_promise_demo();

    // Demonstrates how exception is passed through future
    void run_promise_exception_demo();

    // Demonstrates deferred execution using std::launch::deferred
    void run_deferred_demo();
}

#endif // CPP20_THREAD_H
