// PThreadExample.h
// =====================================================================================
// POSIX pthread multithreading example and synchronization mechanisms demo.
//
// This header declares comprehensive thread-related demonstrations, each showcasing one
// aspect of pthread or POSIX-based synchronization in a clean and safe pattern.
//
// Covered primitives:
// -------------------------------------------------------------------------------------
// 1. Thread creation and joining         (pthread_create / pthread_join)
// 2. Detached threads                    (pthread_detach)
// 3. Mutex locks                         (pthread_mutex_t)
// 4. Condition variables                 (pthread_cond_t)
// 5. Read-Write locks                    (pthread_rwlock_t)
// 6. Barriers                            (pthread_barrier_t)
// 7. Spinlocks                           (pthread_spinlock_t)
// 8. Semaphores                          (sem_t)
// 9. Thread-Local Storage (TLS)         (__thread)
// 10. Thread cancellation                (pthread_cancel)
// 11. Producer-consumer (mutex + cond)  (composite pattern)
//
// Each demo is implemented in the corresponding .cpp file with best practices.
//
// =====================================================================================

#ifndef PTHREAD_EXAMPLE_H
#define PTHREAD_EXAMPLE_H

#include <pthread.h>

/**
 * @brief Demonstrates creating and joining threads using pthreads.
 *
 * - Threads are lightweight processes used to run code concurrently.
 * - `pthread_create` starts a thread with a given function and argument.
 * - `pthread_join` waits for a thread to complete and reclaims resources.
 *
 * Threading is useful for:
 * - parallel computations
 * - I/O handling
 * - responsive applications
 *
 * Use when:
 * - You need to launch threads and wait for their completion before proceeding.
 */
void run_basic_threads();

/**
 * @brief Demonstrates creating detached threads.
 *
 * - Detached threads automatically clean up their resources when they exit.
 * - You must NOT call pthread_join on a detached thread.
 * - Useful for fire-and-forget workers (e.g., loggers, periodic checkers).
 *
 * Use when:
 * - You want threads that run independently and do not require joining.
 */
void run_detached_threads_demo();

/**
 * @brief Demonstrates use of a mutex (mutual exclusion lock).
 *
 * - A `pthread_mutex_t` ensures only one thread can enter a critical section at a time.
 * - Prevents race conditions when threads access shared data.
 * - Always lock/unlock in pairs. Improper usage can lead to deadlock or crashes.
 *
 * Use when:
 * - Multiple threads access shared variables and need exclusive access.
 */
void run_mutex_demo();

/**
 * @brief Demonstrates use of a condition variable for signaling.
 *
 * - Condition variables allow threads to sleep until a specific condition is met.
 * - Must be used with a mutex to protect the associated shared state.
 * - `pthread_cond_wait()` atomically releases the mutex and suspends the thread.
 * - `pthread_cond_signal()` wakes up one waiting thread.
 *
 * Use when:
 * - A thread must wait for another to produce/prepare data (e.g., producer-consumer).
 * - Always use while-loop around `pthread_cond_wait()` to handle spurious wakeups.
 */
void run_condition_demo();

/**
 * @brief Demonstrates read-write locks (pthread_rwlock_t).
 *
 * - Allows multiple readers but only one writer at a time.
 * - Prevents data inconsistency while allowing better read scalability.
 * - `pthread_rwlock_rdlock()` for readers; `pthread_rwlock_wrlock()` for writers.
 *
 * Use when:
 * - Many threads read shared data, but only a few write to it.
 */
void run_rwlock_demo();

/**
 * @brief Demonstrates use of pthread barriers (pthread_barrier_t).
 *
 * - A barrier blocks threads until a fixed number have reached the barrier point.
 * - Once all threads arrive, they all proceed.
 * - Used for coordinating stages in a multi-threaded computation.
 *
 * Use when:
 * - Threads must synchronize at certain checkpoints before continuing.
 */
void run_barrier_demo();

/**
 * @brief Demonstrates thread-local storage using `__thread`.
 *
 * - `__thread` declares a variable that is unique to each thread.
 * - Useful for storing temporary per-thread data without interference.
 * - No locking is required for TLS variables.
 *
 * Use when:
 * - Each thread needs its own version of a variable (e.g., buffers, status).
 */
void run_tls_demo();

/**
 * @brief Demonstrates use of spinlock (busy-waiting mutex).
 *
 * - Spinlocks use busy-waiting instead of sleeping.
 * - Very efficient when hold time is extremely short.
 * - `pthread_spin_lock()` and `pthread_spin_unlock()` are used.
 *
 * Use when:
 * - Critical section is very short and overhead of sleeping is too high.
 */
void run_spinlock_demo();

/**
 * @brief Demonstrates use of semaphore (sem_t).
 *
 * - Semaphore is a counter-based synchronization tool.
 * - `sem_wait()` blocks until the counter is positive.
 * - `sem_post()` increments the counter.
 *
 * Use when:
 * - You want to limit concurrent access to a resource (e.g., max 3 threads at a time).
 */
void run_semaphore_demo();

/**
 * @brief Demonstrates classic producer-consumer model using mutex + condition variable.
 *
 * - Producer pushes data into a shared queue.
 * - Consumer waits on a condition variable until data is available.
 *
 * Use when:
 * - Threads need to coordinate production and consumption of items asynchronously.
 */
void run_producer_consumer_demo();

/**
 * @brief Demonstrates cancelling a thread and using cleanup handlers.
 *
 * - `pthread_cancel()` can request thread termination.
 * - `pthread_cleanup_push/pop` registers cleanup code.
 *
 * Use when:
 * - You want to safely terminate long-running threads and free resources.
 */
void run_cancellation_demo();

#endif // PTHREAD_EXAMPLE_H
