#include "../include/pthread_example.h"
#include <iostream>
#include <unistd.h> // for sleep()
#include <vector>
#include <semaphore.h>
#include <pthread.h>

using namespace std;

// ======================= Thread Creation =======================
void* ThreadFunc(void* arg) {
    int id = *(int*)arg;
    cout << "[Thread " << id << "] running.\n";
    return nullptr;
}

void RunBasicThreads() {
    cout << "=== Thread Creation Demo ===\n";
    pthread_t threads[3];
    vector<int> ids = {0, 1, 2};  // safer than static array

    for (int i = 0; i < 3; ++i) {
        if (pthread_create(&threads[i], nullptr, ThreadFunc, &ids[i]) != 0) {
            perror("Failed to create thread");
        }
    }

    for (int i = 0; i < 3; ++i) {
        pthread_join(threads[i], nullptr); // Must join to avoid resource leak
    }
}

// ======================= Mutex =======================
pthread_mutex_t pthread_mutex = PTHREAD_MUTEX_INITIALIZER;
int shared_counter = 0;

void* MutexWorker(void* /*arg*/) {
    for (int i = 0; i < 100000; ++i) {
        pthread_mutex_lock(&pthread_mutex); // critical section start
        shared_counter++;
        pthread_mutex_unlock(&pthread_mutex); // critical section end
    }
    return nullptr;
}

void RunMutex() {
    cout << "\n=== Mutex Demo ===\n";
    shared_counter = 0;
    pthread_t t1, t2;

    pthread_create(&t1, nullptr, MutexWorker, nullptr);
    pthread_create(&t2, nullptr, MutexWorker, nullptr);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);

    cout << "Final counter value: " << shared_counter << endl;
    pthread_mutex_destroy(&pthread_mutex);
}

// ======================= Condition Variable =======================
pthread_mutex_t cond_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
bool ready = false;

void* Waiter(void*) {
    pthread_mutex_lock(&cond_mutex);
    while (!ready) {
        // Use loop for spurious wakeups
        pthread_cond_wait(&cond, &cond_mutex);
    }
    cout << "[Waiter] Received signal\n";
    pthread_mutex_unlock(&cond_mutex);
    return nullptr;
}

void RunConditionVariable() {
    cout << "\n=== Condition Variable Demo ===\n";
    pthread_t t;
    pthread_create(&t, nullptr, Waiter, nullptr);

    sleep(1); // simulate some preparation
    pthread_mutex_lock(&cond_mutex);
    ready = true;
    pthread_cond_signal(&cond); // signal one waiting thread
    pthread_mutex_unlock(&cond_mutex);

    pthread_join(t, nullptr);
    pthread_mutex_destroy(&cond_mutex);
    pthread_cond_destroy(&cond);
}

// ======================= Read-Write Lock =======================
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;
int shared_data = 0;

void* Reader(void* /*arg*/) {
    pthread_rwlock_rdlock(&rwlock);
    cout << "[Reader] Data = " << shared_data << endl;
    pthread_rwlock_unlock(&rwlock);
    return nullptr;
}

void* Writer(void* /*arg*/) {
    pthread_rwlock_wrlock(&rwlock);
    shared_data++;
    cout << "[Writer] Updated data to " << shared_data << endl;
    pthread_rwlock_unlock(&rwlock);
    return nullptr;
}

void RunReadWriteLock() {
    cout << "\n=== Read-Write Lock Demo ===\n";
    pthread_t r1, r2, w;

    pthread_create(&r1, nullptr, Reader, nullptr);
    pthread_create(&w, nullptr, Writer, nullptr);
    pthread_create(&r2, nullptr, Reader, nullptr);

    pthread_join(r1, nullptr);
    pthread_join(w, nullptr);
    pthread_join(r2, nullptr);

    pthread_rwlock_destroy(&rwlock);
}

// ======================= Barrier =======================
pthread_barrier_t barrier;

void* BarrierTask(void* arg) {
    int id = *(int*)arg;
    cout << "[Thread " << id << "] waiting at barrier...\n";
    pthread_barrier_wait(&barrier); // wait until all threads arrive
    cout << "[Thread " << id << "] passed the barrier\n";
    return nullptr;
}

void RunBarrier() {
    cout << "\n=== Barrier Demo ===\n";
    pthread_barrier_init(&barrier, nullptr, 3); // 3 threads must arrive

    pthread_t t1, t2, t3;
    vector<int> ids = {1, 2, 3};

    pthread_create(&t1, nullptr, BarrierTask, &ids[0]);
    pthread_create(&t2, nullptr, BarrierTask, &ids[1]);
    pthread_create(&t3, nullptr, BarrierTask, &ids[2]);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    pthread_join(t3, nullptr);

    pthread_barrier_destroy(&barrier);
}

// ======================= Thread Local Storage =======================
__thread int tls_var = 0;  // Each thread gets its own tls_var

void* TlsFunc(void* arg) {
    int id = *(int*)arg;
    tls_var = id * 10;
    cout << "[Thread " << id << "] TLS var = " << tls_var << endl;
    return nullptr;
}

void RunTls() {
    cout << "\n=== TLS Demo ===\n";
    pthread_t t1, t2;
    vector<int> ids = {1, 2};

    pthread_create(&t1, nullptr, TlsFunc, &ids[0]);
    pthread_create(&t2, nullptr, TlsFunc, &ids[1]);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
}

// ======================= Spinlock =======================
pthread_spinlock_t spinlock;
int spin_counter = 0;

void* SpinWorker(void*) {
    for (int i = 0; i < 100000; ++i) {
        pthread_spin_lock(&spinlock);
        spin_counter++;
        pthread_spin_unlock(&spinlock);
    }
    return nullptr;
}

void RunSpinlock() {
    cout << "\n=== Spinlock Demo ===\n";
    spin_counter = 0;
    pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);

    pthread_t t1, t2;
    pthread_create(&t1, nullptr, SpinWorker, nullptr);
    pthread_create(&t2, nullptr, SpinWorker, nullptr);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);

    pthread_spin_destroy(&spinlock);
    cout << "Final spin_counter: " << spin_counter << endl;
}

// ======================= Semaphore =======================
sem_t semaphore;
int sem_counter = 0;

void* SemWorker(void* arg) {
    int id = *(int*)arg;

    sem_wait(&semaphore);
    cout << "[Thread " << id << "] entered critical section\n";

    sleep(1);
    sem_counter++;

    cout << "[Thread " << id << "] exiting\n";
    sem_post(&semaphore);
    return nullptr;
}

void RunSemaphore() {
    cout << "\n=== Semaphore Demo ===\n";

    const int max_concurrent = 2;
    const int thread_count = 5;
    sem_init(&semaphore, 0, max_concurrent);
    pthread_t threads[thread_count];
    vector<int> ids(thread_count);

    for (int i = 0; i < thread_count; ++i) {
        ids[i] = i;
        pthread_create(&threads[i], nullptr, SemWorker, &ids[i]);
    }

    for (int i = 0; i < thread_count; ++i) {
        pthread_join(threads[i], nullptr);
    }

    sem_destroy(&semaphore);
    cout << "Total threads passed: " << sem_counter << endl;
}

// ======================= Detached Threads =======================
void* DetachedTask(void* arg) {
    int id = *(int*)arg;
    cout << "[Detached Thread " << id << "] running and detaching\n";
    sleep(1);
    cout << "[Detached Thread " << id << "] exiting\n";
    return nullptr;
}

void RunDetachedThreads() {
    cout << "\n=== Detached Threads Demo ===\n";
    pthread_t t;
    int id = 1;
    pthread_create(&t, nullptr, DetachedTask, &id);
    pthread_detach(t);
    sleep(2);
}

// ======================= Cancellation Demo =======================
void CleanUp(void* /*arg*/) {
    cout << "[Thread] Cleanup handler called." << endl;
}

void* CancellableWorker(void* /*arg*/) {
    pthread_cleanup_push(CleanUp, nullptr);
    for (int i = 0; i < 5; ++i) {
        cout << "[Worker] Working...\n";
        sleep(1);
    }
    pthread_cleanup_pop(0);
    return nullptr;
}

void RunCancellation() {
    cout << "\n=== Cancellation Demo ===\n";
    pthread_t t;
    pthread_create(&t, nullptr, CancellableWorker, nullptr);
    sleep(2);
    pthread_cancel(t);
    pthread_join(t, nullptr);
    cout << "[Main] Thread cancelled\n";
}

// ======================= Producer-Consumer =======================
#include <queue>

pthread_mutex_t pc_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t pc_not_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t pc_not_full = PTHREAD_COND_INITIALIZER;

queue<int> buffer;
const int MAX_BUFFER_SIZE = 5;
bool done = false;

void* Producer(void*) {
    for (int i = 1; i <= 10; ++i) {
        pthread_mutex_lock(&pc_mutex);
        while (buffer.size() == MAX_BUFFER_SIZE) {
            pthread_cond_wait(&pc_not_full, &pc_mutex);
        }
        buffer.push(i);
        cout << "[Producer] Produced: " << i << endl;
        pthread_cond_signal(&pc_not_empty);
        pthread_mutex_unlock(&pc_mutex);
        sleep(1); // simulate work
    }

    pthread_mutex_lock(&pc_mutex);
    done = true;
    pthread_cond_broadcast(&pc_not_empty); // wake up all consumers
    pthread_mutex_unlock(&pc_mutex);
    return nullptr;
}

void* Consumer(void* arg) {
    int id = *(int*)arg;
    while (true) {
        pthread_mutex_lock(&pc_mutex);
        while (buffer.empty() && !done) {
            pthread_cond_wait(&pc_not_empty, &pc_mutex);
        }

        if (buffer.empty() && done) {
            pthread_mutex_unlock(&pc_mutex);
            break;
        }

        int item = buffer.front();
        buffer.pop();
        cout << "[Consumer " << id << "] Consumed: " << item << endl;
        pthread_cond_signal(&pc_not_full);
        pthread_mutex_unlock(&pc_mutex);
        sleep(2); // simulate processing
    }
    return nullptr;
}

void RunProducerConsumer() {
    cout << "\n=== Producer-Consumer Demo ===\n";
    buffer = queue<int>();
    done = false;

    pthread_t prod, cons1, cons2;
    int cid1 = 1, cid2 = 2;

    pthread_create(&prod, nullptr, Producer, nullptr);
    pthread_create(&cons1, nullptr, Consumer, &cid1);
    pthread_create(&cons2, nullptr, Consumer, &cid2);

    pthread_join(prod, nullptr);
    pthread_join(cons1, nullptr);
    pthread_join(cons2, nullptr);

    pthread_mutex_destroy(&pc_mutex);
    pthread_cond_destroy(&pc_not_empty);
    pthread_cond_destroy(&pc_not_full);
}
