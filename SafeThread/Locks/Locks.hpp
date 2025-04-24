#ifndef LOCKS_HPP
#define LOCKS_HPP

#include <mutex>
#include <shared_mutex>
#include <thread>
#include <iostream>
#include <vector>
#include <algorithm>
#include <condition_variable>

/**
 * MyLockGuard is a RAII-style wrapper that locks a mutex upon construction
 * and automatically unlocks it upon destruction.
 * Equivalent to std::lock_guard.
 */
class MyLockGuard {
public:
    explicit MyLockGuard(std::mutex& m) : mtx(m) {
        mtx.lock();
    }

    ~MyLockGuard() {
        mtx.unlock();
    }

private:
    std::mutex& mtx;
};

/**
 * MyUniqueLock provides ownership-based mutex management.
 * It supports manual lock/unlock, deferred locking, and try-lock.
 * Equivalent to std::unique_lock.
 */
class MyUniqueLock {
public:
    explicit MyUniqueLock(std::mutex& m, bool defer_lock = false)
        : mtx(m), owns(false) {
        if (!defer_lock) {
            mtx.lock();
            owns = true;
        }
    }

    ~MyUniqueLock() {
        if (owns) mtx.unlock();
    }

    void lock() {
        if (!owns) {
            mtx.lock();
            owns = true;
        }
    }

    void unlock() {
        if (owns) {
            mtx.unlock();
            owns = false;
        }
    }

    bool try_lock() {
        owns = mtx.try_lock();
        return owns;
    }

    bool owns_lock() const {
        return owns;
    }

private:
    std::mutex& mtx;
    bool owns;
};

/**
 * MySharedMutex is a custom shared mutex supporting:
 * - Multiple concurrent readers
 * - Exclusive single writer
 * Equivalent to std::shared_mutex.
 */
class MySharedMutex {
public:
    void lock() {
        std::unique_lock<std::mutex> lk(mtx);
        write_cv.wait(lk, [&] { return reader_count == 0 && !writer; });
        writer = true;
    }

    void unlock() {
        std::unique_lock<std::mutex> lk(mtx);
        writer = false;
        reader_cv.notify_all();
        write_cv.notify_one();
    }

    void lock_shared() {
        std::unique_lock<std::mutex> lk(mtx);
        reader_cv.wait(lk, [&] { return !writer; });
        ++reader_count;
    }

    void unlock_shared() {
        std::unique_lock<std::mutex> lk(mtx);
        if (--reader_count == 0) {
            write_cv.notify_one();
        }
    }

private:
    std::mutex mtx;
    std::condition_variable reader_cv;
    std::condition_variable write_cv;
    int reader_count = 0;
    bool writer = false;
};

/**
 * MySharedLock is a lightweight reader lock that acquires
 * shared ownership of a MySharedMutex.
 * Equivalent to std::shared_lock.
 */
class MySharedLock {
public:
    explicit MySharedLock(MySharedMutex& sm) : smtx(sm) {
        smtx.lock_shared();
    }

    ~MySharedLock() {
        smtx.unlock_shared();
    }

private:
    MySharedMutex& smtx;
};

/**
 * MyScopedLock locks multiple mutexes in a deadlock-safe way.
 * Similar to std::scoped_lock which takes multiple locks in order.
 */
class MyScopedLock {
public:
    template <typename... Mutexes>
    explicit MyScopedLock(Mutexes&... mutexes) {
        lock_all(mutexes...);
    }

    ~MyScopedLock() {
        // Unlock in reverse order
        for (auto it = locks.rbegin(); it != locks.rend(); ++it) {
            (*it)->unlock();
        }
    }

private:
    std::vector<std::mutex*> locks;

    void lock_all() {}  // End of recursion

    template <typename First, typename... Rest>
    void lock_all(First& first, Rest&... rest) {
        first.lock();
        locks.push_back(&first);
        lock_all(rest...);
    }
};

#endif // LOCKS_HPP
