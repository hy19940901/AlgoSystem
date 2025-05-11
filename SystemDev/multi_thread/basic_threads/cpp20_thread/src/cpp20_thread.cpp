#include "../include/cpp20_thread.h"
#include <iostream>

using namespace std;

namespace thread_demo {
// ======================= Thread Creation =======================
/**
 * @brief Simulated heavy computation task for benchmarking threads.
 *
 * Each thread performs a different number of square root operations to simulate
 * variable task durations. The actual runtime will be roughly 100ms–300ms
 * depending on the CPU and workload size.
 *
 * @param id Thread identifier (used to scale the workload)
 */
void thread_task(int id) {
    // Simulate workload size based on thread id (more id → more work)
    const int work_size = 8'000'000 + id * 2'000'000;

    // Dummy result to prevent compiler optimizing the loop away
    double result = 0.0;

    // Start measuring time (optional for detailed log)
    auto start = std::chrono::high_resolution_clock::now();

    // Perform heavy floating-point calculations
    for (int i = 1; i < work_size; ++i) {
        result += std::sqrt(i * 1.0);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // Output the result and thread details
    std::cout << "[Thread " << id << "] finished task (size = " << work_size
              << ") in " << elapsed << " ms, result = " << static_cast<long long>(result)
              << ", thread ID = " << std::this_thread::get_id() << std::endl;
}

void run_basic_threads() {
    cout << "=== Thread Creation Demo ===" << endl;
    vector<thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(thread_task, i);
    }
    for (auto& t : threads) {
        t.join();
    }
}

// ======================= Detached Threads =======================
void detached_task(int id) {
    cout << "[Detached Thread " << id << "] running." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "[Detached Thread " << id << "] exiting." << endl;
}

void run_detached_threads_demo() {
    cout << "\n=== Detached Threads Demo ===" << endl;
    thread t(detached_task, 1);
    t.detach();
    this_thread::sleep_for(chrono::seconds(2));
}

// ======================= Mutex =======================
mutex g_mutex;
int g_counter = 0;

void mutex_worker() {
    for (int i = 0; i < 100000; ++i) {
        lock_guard<mutex> lock(g_mutex);
        ++g_counter;
    }
}

void run_mutex_demo() {
    cout << "\n=== Mutex Demo ===" << endl;
    g_counter = 0;
    thread t1(mutex_worker);
    thread t2(mutex_worker);
    t1.join();
    t2.join();
    cout << "Final counter value: " << g_counter << endl;
}

// ======================= Condition Variable =======================
mutex cv_mutex;
condition_variable cv;
bool ready = false;

void cv_waiter() {
    unique_lock<mutex> lock(cv_mutex);
    cv.wait(lock, [] { return ready; });
    cout << "[CV Waiter] Received signal." << endl;
}

void run_condition_demo() {
    cout << "\n=== Condition Variable Demo ===" << endl;
    thread t(cv_waiter);
    this_thread::sleep_for(chrono::seconds(1));
    {
        lock_guard<mutex> lock(cv_mutex);
        ready = true;
    }
    cv.notify_one();
    t.join();
}

// ======================= Shared Mutex (RW Lock) =======================
shared_mutex rw_mutex;
int shared_data = 0;

void reader_task(int id) {
    shared_lock<shared_mutex> lock(rw_mutex);
    cout << "[Reader " << id << "] Read: " << shared_data << endl;
}

void writer_task() {
    unique_lock<shared_mutex> lock(rw_mutex);
    ++shared_data;
    cout << "[Writer] Updated data to: " << shared_data << endl;
}

void run_rwlock_demo() {
    cout << "\n=== Read-Write Lock Demo ===" << endl;
    thread r1(reader_task, 1);
    thread w(writer_task);
    thread r2(reader_task, 2);
    r1.join();
    w.join();
    r2.join();
}

// ======================= Barrier =======================
barrier sync_point(3);

void barrier_task(int id) {
    cout << "[Thread " << id << "] waiting at barrier..." << endl;
    sync_point.arrive_and_wait();
    cout << "[Thread " << id << "] passed the barrier." << endl;
}

void run_barrier_demo() {
    cout << "\n=== Barrier Demo ===" << endl;
    thread t1(barrier_task, 1);
    thread t2(barrier_task, 2);
    thread t3(barrier_task, 3);
    t1.join();
    t2.join();
    t3.join();
}

// ======================= TLS =======================
thread_local int tls_var = 0;

void tls_task(int id) {
    tls_var = id * 10;
    cout << "[Thread " << id << "] TLS var = " << tls_var << endl;
}

void run_tls_demo() {
    cout << "\n=== TLS Demo ===" << endl;
    thread t1(tls_task, 1);
    thread t2(tls_task, 2);
    t1.join();
    t2.join();
}

// ======================= Spinlock =======================
atomic_flag spinlock = ATOMIC_FLAG_INIT;
int spin_counter = 0;

void spin_worker() {
    for (int i = 0; i < 100000; ++i) {
        while (spinlock.test_and_set(std::memory_order_acquire));
        ++spin_counter;
        spinlock.clear(std::memory_order_release);
    }
}

void run_spinlock_demo() {
    cout << "\n=== Spinlock Demo ===" << endl;
    spin_counter = 0;
    thread t1(spin_worker);
    thread t2(spin_worker);
    t1.join();
    t2.join();
    cout << "Final spin_counter: " << spin_counter << endl;
}

// ======================= Semaphore =======================
counting_semaphore<3> sem(2);
int sem_counter = 0;

void sem_worker(int id) {
    sem.acquire();
    cout << "[Thread " << id << "] entered." << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
    ++sem_counter;
    cout << "[Thread " << id << "] exiting." << endl;
    sem.release();
}

void run_semaphore_demo() {
    cout << "\n=== Semaphore Demo ===" << endl;
    vector<thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(sem_worker, i);
    }
    for (auto& t : threads) t.join();
    cout << "Total threads passed: " << sem_counter << endl;
}

// ======================= Producer-Consumer =======================
queue<int> buffer;
mutex pc_mutex;
condition_variable pc_cv;
const int MAX_BUFFER = 5;
bool pc_done = false;

void producer() {
    for (int i = 1; i <= 10; ++i) {
        unique_lock<mutex> lock(pc_mutex);
        pc_cv.wait(lock, [] { return buffer.size() < MAX_BUFFER; });
        buffer.push(i);
        cout << "[Producer] Produced: " << i << endl;
        pc_cv.notify_all();
    }
    pc_done = true;
    pc_cv.notify_all();
}

void consumer(int id) {
    while (true) {
        unique_lock<mutex> lock(pc_mutex);
        pc_cv.wait(lock, [] { return !buffer.empty() || pc_done; });
        if (buffer.empty() && pc_done) break;
        int val = buffer.front(); buffer.pop();
        cout << "[Consumer " << id << "] Consumed: " << val << endl;
        pc_cv.notify_all();
    }
}

void run_producer_consumer_demo() {
    cout << "\n=== Producer-Consumer Demo ===" << endl;
    thread prod(producer);
    thread cons1(consumer, 1);
    thread cons2(consumer, 2);
    prod.join();
    cons1.join();
    cons2.join();
}

// ======================= Cancellation Demo =======================
atomic<bool> cancel_flag(false);

void cancel_worker() {
    for (int i = 0; i < 10; ++i) {
        if (cancel_flag.load()) {
            cout << "[Worker] Cancelled early." << endl;
            return;
        }
        cout << "[Worker] Working..." << endl;
        this_thread::sleep_for(chrono::milliseconds(300));
    }
}

void run_cancellation_demo() {
    cout << "\n=== Cancellation Demo ===" << endl;
    cancel_flag = false;
    thread t(cancel_worker);
    this_thread::sleep_for(chrono::milliseconds(800));
    cancel_flag = true;
    t.join();
}

void run_thread_benchmark() {
    cout << "\n=== Thread Benchmark Demo ===" << endl;
    const int num_threads = 4;
    const int num_iterations = 10'000'000;

    // Single-thread baseline
    int counter_single = 0;
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < num_threads * num_iterations; ++i) {
        ++counter_single;
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "[Single-thread] Time: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << " ms, Result: " << counter_single << endl;

    // Multi-threaded with mutex
    int counter_mutex = 0;
    mutex mtx;
    start = chrono::high_resolution_clock::now();
    {
        vector<thread> threads;
        for (int i = 0; i < num_threads; ++i) {
            threads.emplace_back([&]() {
                for (int j = 0; j < num_iterations; ++j) {
                    lock_guard<mutex> lock(mtx);
                    ++counter_mutex;
                }
            });
        }
        for (auto& t : threads) t.join();
    }
    end = chrono::high_resolution_clock::now();
    cout << "[Multi-thread mutex] Time: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << " ms, Result: " << counter_mutex << endl;

    // Multi-threaded with atomic
    atomic<int> counter_atomic = 0;
    start = chrono::high_resolution_clock::now();
    {
        vector<thread> threads;
        for (int i = 0; i < num_threads; ++i) {
            threads.emplace_back([&]() {
                for (int j = 0; j < num_iterations; ++j) {
                    ++counter_atomic;
                }
            });
        }
        for (auto& t : threads) t.join();
    }
    end = chrono::high_resolution_clock::now();
    cout << "[Multi-thread atomic] Time: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << " ms, Result: " << counter_atomic.load() << endl;
}

void run_parallel_vs_serial_benchmark() {
    cout << "\n=== Parallel vs Serial Benchmark (Heavy Task) ===" << endl;
    const int num_threads = 4;
    const int N = 40'000'000;
    vector<int> data(N, 1);

    // Simulated heavy task
    auto heavy_compute = [](int& x) {
        for (int i = 0; i < 100; ++i) {
            x = (x * 31 + 7) % 100000;
        }
    };

    // Serial version
    auto start = chrono::high_resolution_clock::now();
    for (int& x : data) {
        heavy_compute(x);
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "[Serial] Time: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << " ms\n";

    // Reset data
    fill(data.begin(), data.end(), 1);

    // Parallel version
    start = chrono::high_resolution_clock::now();
    vector<thread> threads;
    int chunk = N / num_threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&, i]() {
            int begin = i * chunk;
            int end = (i == num_threads - 1) ? N : begin + chunk;
            for (int j = begin; j < end; ++j) {
                heavy_compute(data[j]);
            }
        });
    }
    for (auto& t : threads) t.join();
    end = chrono::high_resolution_clock::now();
    cout << "[Parallel] Time: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << " ms\n";
}

}

// ======================= Future: std::future, shared_future, etc =======================
namespace future_demo {

void run_future_demo() {
    cout << "\n=== Future / Async Demo ===" << endl;
    auto factorial = [](int n) -> int {
        this_thread::sleep_for(chrono::milliseconds(500));
        int result = 1;
        for (int i = 2; i <= n; ++i) result *= i;
        return result;
    };
    future<int> fut = async(launch::async, factorial, 5);
    cout << "Doing other work while waiting for future..." << endl;
    this_thread::sleep_for(chrono::milliseconds(200));
    int result = fut.get();
    cout << "Factorial(5) = " << result << endl;
}

void run_packaged_task_demo() {
    cout << "\n=== Packaged Task Demo ===" << endl;
    packaged_task<int(int)> task([](int x) {
        this_thread::sleep_for(chrono::milliseconds(300));
        return x * x;
    });
    future<int> fut = task.get_future();
    thread t(move(task), 7);
    cout << "Square = " << fut.get() << endl;
    t.join();
}

void run_shared_future_demo() {
    cout << "\n=== Shared Future Demo ===" << endl;
    promise<string> prom;
    shared_future<string> sfut = prom.get_future().share();
    auto reader = [](shared_future<string> f, int id) {
        cout << "[Reader " << id << "] got: " << f.get() << endl;
    };
    thread t1(reader, sfut, 1);
    thread t2(reader, sfut, 2);
    this_thread::sleep_for(chrono::milliseconds(200));
    prom.set_value("shared result");
    t1.join();
    t2.join();
}

void run_wait_for_demo() {
    cout << "\n=== Future wait_for() Demo ===" << endl;
    future<int> fut = async(launch::async, [] {
        this_thread::sleep_for(chrono::seconds(2));
        return 100;
    });
    if (fut.wait_for(chrono::milliseconds(1000)) == future_status::timeout) {
        cout << "Timeout: task still running\n";
    } else {
        cout << "Result = " << fut.get() << endl;
    }
}

void run_promise_demo() {
    cout << "\n=== Promise Value Demo ===" << endl;
    promise<int> prom;
    future<int> fut = prom.get_future();
    thread t([&prom]() {
        this_thread::sleep_for(chrono::milliseconds(300));
        prom.set_value(42);
    });
    cout << "Promise set value = " << fut.get() << endl;
    t.join();
}

void run_promise_exception_demo() {
    cout << "\n=== Promise Exception Demo ===" << endl;
    promise<int> prom;
    future<int> fut = prom.get_future();
    thread t([&prom]() {
        try {
            throw runtime_error("Something went wrong");
        } catch (...) {
            prom.set_exception(current_exception());
        }
    });
    try {
        int value = fut.get(); // will throw
        cout << "Should not print: " << value << endl;
    } catch (const exception& e) {
        cout << "Caught exception: " << e.what() << endl;
    }
    t.join();
}

void run_deferred_demo() {
    cout << "\n=== Deferred Launch Demo ===" << endl;
    auto lazy = async(launch::deferred, [] {
        cout << "Deferred task starting now\n";
        return 55;
    });
    cout << "Nothing runs until get()...\n";
    int val = lazy.get(); // triggers execution
    cout << "Deferred result = " << val << endl;
}

} // namespace future_demo
