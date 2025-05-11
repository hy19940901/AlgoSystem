#include "../include/pthread_example.h"

int main() {
    RunBasicThreads();                // 1. Basic thread creation
    RunDetachedThreads();       // 2. Detached thread
    RunMutex();                  // 3. Mutex demo
    RunConditionVariable();              // 4. Condition variable
    RunReadWriteLock();                 // 5. Read-write lock
    RunBarrier();                // 6. Barrier synchronization
    RunTls();                    // 7. Thread-local storage (__thread)
    RunSpinlock();              // 8. Spinlock usage
    RunSemaphore();             // 9. Semaphore usage
    RunProducerConsumer();     // 10. Producer-consumer (TODO: implement)
    RunCancellation();          // 11. Thread cancellation with cleanup

    return 0;
}
