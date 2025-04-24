#include "Lock.hpp"

MySharedMutex smtx;
int shared_data = 0;

void reader(int id) {
    MySharedLock lock(smtx);
    std::cout << "[reader] Thread " << id << " reads " << shared_data << "\n";
}

void writer(int id) {
    MyUniqueLock lock(reinterpret_cast<std::mutex&>(smtx));
    ++shared_data;
    std::cout << "[writer] Thread " << id << " writes " << shared_data << "\n";
}

int main() {
    std::mutex m1, m2;

    {
        MyScopedLock scoped(m1, m2);  // Both locked, safe
        std::cout << "[scoped_lock] Two mutexes locked without deadlock\n";
    }

    std::thread t1(reader, 1);
    std::thread t2(reader, 2);
    std::thread t3(writer, 3);

    t1.join(); t2.join(); t3.join();

    return 0;
}
