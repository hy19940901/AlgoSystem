#include "ThreadPool.hpp"
#include <iostream>

int main() {
    ThreadPool full_pool(4);
    SimpleThreadPool simple_pool(2);

    // 有返回值
    auto fut = full_pool.submit([] { return 123; });
    std::cout << "FullPool result: " << fut.get() << std::endl;

    // 无返回值
    simple_pool.post([] {
        std::cout << "SimplePool task running\n";
    });

    return 0;
}
