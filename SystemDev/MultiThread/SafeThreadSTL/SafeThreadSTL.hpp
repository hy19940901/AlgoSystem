// thread_safe_stl.hpp
#ifndef SAFT_THREAD_STL_HPP
#define SAFT_THREAD_STL_HPP

#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <optional>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <list>
#include <chrono>

namespace thread_safe {

// ====================== Non-blocking Containers ====================== //
namespace non_blocking {

/**
 * @brief Thread-safe std::vector wrapper using std::mutex.
 *        Provides push_back, try_get, size, and empty methods.
 */
template <typename T>
class Vector {
public:
    void push_back(const T& value) {
        std::lock_guard<std::mutex> lock(mtx_);
        data_.push_back(value);
    }

    std::optional<T> try_get(size_t index) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (index >= data_.size()) return std::nullopt;
        return data_[index];
    }

    size_t size() {
        std::lock_guard<std::mutex> lock(mtx_);
        return data_.size();
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(mtx_);
        return data_.empty();
    }

private:
    std::vector<T> data_;
    std::mutex mtx_;
};

/**
 * @brief Thread-safe std::deque wrapper.
 */
template <typename T>
class Deque {
public:
    void push_back(const T& value) {
        std::lock_guard<std::mutex> lock(mtx_);
        data_.push_back(value);
    }

    void push_front(const T& value) {
        std::lock_guard<std::mutex> lock(mtx_);
        data_.push_front(value);
    }

    bool try_pop_front(T& result) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (data_.empty()) return false;
        result = data_.front();
        data_.pop_front();
        return true;
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(mtx_);
        return data_.empty();
    }

    size_t size() {
        std::lock_guard<std::mutex> lock(mtx_);
        return data_.size();
    }

private:
    std::deque<T> data_;
    std::mutex mtx_;
};

/**
 * @brief Thread-safe std::stack wrapper.
 */
template <typename T>
class Stack {
public:
    void push(const T& value) {
        std::lock_guard<std::mutex> lock(mtx_);
        data_.push(value);
    }

    bool try_pop(T& result) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (data_.empty()) return false;
        result = data_.top();
        data_.pop();
        return true;
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(mtx_);
        return data_.empty();
    }

private:
    std::stack<T> data_;
    std::mutex mtx_;
};

/**
 * @brief Thread-safe std::queue wrapper.
 */
template <typename T>
class Queue {
public:
    void push(const T& value) {
        std::lock_guard<std::mutex> lock(mtx_);
        data_.push(value);
    }

    bool try_pop(T& result) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (data_.empty()) return false;
        result = data_.front();
        data_.pop();
        return true;
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(mtx_);
        return data_.empty();
    }

private:
    std::queue<T> data_;
    std::mutex mtx_;
};

/**
 * @brief Thread-safe std::priority_queue wrapper.
 */
template <typename T>
class PriorityQueue {
public:
    void push(const T& value) {
        std::lock_guard<std::mutex> lock(mtx_);
        data_.push(value);
    }

    bool try_pop(T& result) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (data_.empty()) return false;
        result = data_.top();
        data_.pop();
        return true;
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(mtx_);
        return data_.empty();
    }

private:
    std::priority_queue<T> data_;
    std::mutex mtx_;
};

/**
 * @brief Thread-safe std::map wrapper.
 */
template <typename K, typename V>
class Map {
public:
    void insert(const K& key, const V& value) {
        std::unique_lock lock(mtx_);
        data_[key] = value;
    }

    bool try_get(const K& key, V& result) {
        std::shared_lock lock(mtx_);
        auto it = data_.find(key);
        if (it == data_.end()) return false;
        result = it->second;
        return true;
    }

    bool empty() {
        std::shared_lock lock(mtx_);
        return data_.empty();
    }

private:
    std::map<K, V> data_;
    std::shared_mutex mtx_;
};

/**
 * @brief Thread-safe std::unordered_map wrapper.
 */
template <typename K, typename V>
class UnorderedMap {
public:
    void insert(const K& key, const V& value) {
        std::unique_lock lock(mtx_);
        data_[key] = value;
    }

    bool try_get(const K& key, V& result) {
        std::shared_lock lock(mtx_);
        auto it = data_.find(key);
        if (it == data_.end()) return false;
        result = it->second;
        return true;
    }

    bool empty() {
        std::shared_lock lock(mtx_);
        return data_.empty();
    }

private:
    std::unordered_map<K, V> data_;
    std::shared_mutex mtx_;
};

/**
 * @brief Thread-safe std::set wrapper.
 */
template <typename T>
class Set {
public:
    void insert(const T& value) {
        std::unique_lock lock(mtx_);
        data_.insert(value);
    }

    bool contains(const T& value) {
        std::shared_lock lock(mtx_);
        return data_.find(value) != data_.end();
    }

    bool empty() {
        std::shared_lock lock(mtx_);
        return data_.empty();
    }

private:
    std::set<T> data_;
    std::shared_mutex mtx_;
};

/**
 * @brief Thread-safe std::unordered_set wrapper.
 */
template <typename T>
class UnorderedSet {
public:
    void insert(const T& value) {
        std::unique_lock lock(mtx_);
        data_.insert(value);
    }

    bool contains(const T& value) {
        std::shared_lock lock(mtx_);
        return data_.find(value) != data_.end();
    }

    bool empty() {
        std::shared_lock lock(mtx_);
        return data_.empty();
    }

private:
    std::unordered_set<T> data_;
    std::shared_mutex mtx_;
};

} // namespace non_blocking

// ====================== Blocking Containers ====================== //
namespace blocking {
/**
 * @brief Blocking thread-safe queue with condition_variable.
 *        wait_and_pop() blocks until an element is available.
 */
template <typename T>
class Queue {
public:
    void push(const T& value) {
        {
            std::lock_guard<std::mutex> lock(mtx_);
            data_.push(value);
        }
        cv_.notify_one();  // Notify one waiting thread
    }

    T wait_and_pop() {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_.wait(lock, [this] { return !data_.empty(); });
        T value = data_.front();
        data_.pop();
        return value;
    }

    bool wait_and_pop(T& value, std::chrono::milliseconds timeout) {
        std::unique_lock<std::mutex> lock(mtx_);
        if (!cv_.wait_for(lock, timeout, [this] { return !data_.empty(); }))
            return false;
        value = data_.front();
        data_.pop();
        return true;
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(mtx_);
        return data_.empty();
    }

    size_t size() {
        std::lock_guard<std::mutex> lock(mtx_);
        return data_.size();
    }

private:
    std::queue<T> data_;
    std::mutex mtx_;
    std::condition_variable cv_;
};

/**
 * @brief Blocking thread-safe stack using condition_variable.
 */
template <typename T>
class Stack {
public:
    void push(const T& value) {
        {
            std::lock_guard<std::mutex> lock(mtx_);
            data_.push(value);
        }
        cv_.notify_one();
    }

    T wait_and_pop() {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_.wait(lock, [this] { return !data_.empty(); });
        T value = data_.top();
        data_.pop();
        return value;
    }

    bool wait_and_pop(T& value, std::chrono::milliseconds timeout) {
        std::unique_lock<std::mutex> lock(mtx_);
        if (!cv_.wait_for(lock, timeout, [this] { return !data_.empty(); }))
            return false;
        value = data_.top();
        data_.pop();
        return true;
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(mtx_);
        return data_.empty();
    }

private:
    std::stack<T> data_;
    std::mutex mtx_;
    std::condition_variable cv_;
};

/**
 * @brief Blocking thread-safe list with wait_and_pop_front.
 */
template <typename T>
class List {
public:
    void push_back(const T& value) {
        {
            std::lock_guard<std::mutex> lock(mtx_);
            data_.push_back(value);
        }
        cv_.notify_one();
    }

    T wait_and_pop_front() {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_.wait(lock, [this] { return !data_.empty(); });
        T value = data_.front();
        data_.pop_front();
        return value;
    }

    bool wait_and_pop_front(T& value, std::chrono::milliseconds timeout) {
        std::unique_lock<std::mutex> lock(mtx_);
        if (!cv_.wait_for(lock, timeout, [this] { return !data_.empty(); }))
            return false;
        value = data_.front();
        data_.pop_front();
        return true;
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(mtx_);
        return data_.empty();
    }

private:
    std::list<T> data_;
    std::mutex mtx_;
    std::condition_variable cv_;
};

} // namespace thread_safe::blocking
    
} // namespace thread_safe

#endif // SAFT_THREAD_STL_HPP
