#include "thread_safe_stl.hpp"
#include <thread>
#include <iostream>
#include <chrono>

using namespace std::chrono_literals;

void test_non_blocking() {
    thread_safe::non_blocking::Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    if (auto val = v.try_get(1); val.has_value())
        std::cout << "[NonBlocking::Vector] Got: " << *val << "\n";

    thread_safe::non_blocking::Queue<int> q;
    q.push(10);
    int val;
    if (q.try_pop(val))
        std::cout << "[NonBlocking::Queue] Popped: " << val << "\n";

    thread_safe::non_blocking::Map<std::string, int> m;
    m.insert("key", 42);
    if (m.try_get("key", val))
        std::cout << "[NonBlocking::Map] Got: " << val << "\n";
}

void test_blocking() {
    thread_safe::blocking::Queue<int> q;
    std::thread producer([&]() {
        std::this_thread::sleep_for(500ms);
        q.push(100);
        std::cout << "[Blocking::Queue] Pushed: 100\n";
    });

    int val = q.wait_and_pop();
    std::cout << "[Blocking::Queue] Waited and got: " << val << "\n";
    producer.join();

    thread_safe::blocking::List<int> lst;
    std::thread writer([&]() {
        std::this_thread::sleep_for(300ms);
        lst.push_back(77);
        std::cout << "[Blocking::List] Pushed: 77\n";
    });

    val = lst.wait_and_pop_front();
    std::cout << "[Blocking::List] Got front: " << val << "\n";
    writer.join();
}

int main() {
    std::cout << "=== Non-blocking tests ===\n";
    test_non_blocking();

    std::cout << "\n=== Blocking tests ===\n";
    test_blocking();

    return 0;
}
