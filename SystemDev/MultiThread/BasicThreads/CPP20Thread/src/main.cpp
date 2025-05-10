#include "../include/CPP20Thread.h"

int main() {
    thread_demo::run_basic_threads();
    thread_demo::run_detached_threads_demo();
    thread_demo::run_mutex_demo();
    thread_demo::run_condition_demo();
    thread_demo::run_rwlock_demo();
    thread_demo::run_barrier_demo();
    thread_demo::run_tls_demo();
    thread_demo::run_spinlock_demo();
    thread_demo::run_semaphore_demo();
    thread_demo::run_producer_consumer_demo();
    thread_demo::run_cancellation_demo();

    future_demo::run_wait_for_demo();
    future_demo::run_promise_demo();
    future_demo::run_promise_exception_demo();
    future_demo::run_deferred_demo();

    thread_demo::run_thread_benchmark();
    thread_demo::run_parallel_vs_serial_benchmark();
    return 0;
}
