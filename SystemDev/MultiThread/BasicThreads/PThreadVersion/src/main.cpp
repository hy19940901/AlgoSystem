#include "../include/PThreadExample.h"

int main() {
    run_basic_threads();                // 1. Basic thread creation
    run_detached_threads_demo();       // 2. Detached thread
    run_mutex_demo();                  // 3. Mutex demo
    run_condition_demo();              // 4. Condition variable
    run_rwlock_demo();                 // 5. Read-write lock
    run_barrier_demo();                // 6. Barrier synchronization
    run_tls_demo();                    // 7. Thread-local storage (__thread)
    run_spinlock_demo();              // 8. Spinlock usage
    run_semaphore_demo();             // 9. Semaphore usage
    run_producer_consumer_demo();     // 10. Producer-consumer (TODO: implement)
    run_cancellation_demo();          // 11. Thread cancellation with cleanup

    return 0;
}
