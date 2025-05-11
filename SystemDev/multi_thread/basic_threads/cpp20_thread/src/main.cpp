#include "../include/cpp20_thread.h"
#include <iostream>

int main() {
    using namespace thread_demo;
    using namespace future_demo;

    std::cout << "\n===== Threading Demos =====" << std::endl;
    BasicThreadsDemo().Run();
    DetachedThreadsDemo().Run();
    MutexDemo().Run();
    ConditionDemo().Run();
    RwlockDemo().Run();
    BarrierDemo().Run();
    TlsDemo().Run();
    SpinlockDemo().Run();
    SemaphoreDemo().Run();
    ProducerConsumerDemo().Run();
    CancellationDemo().Run();
    ThreadBenchmarkDemo().Run();
    ParallelVsSerialDemo().Run();

    std::cout << "\n===== Future / Async Demos =====" << std::endl;
    FutureDemo::Run();
    PackagedTaskDemo::Run();
    SharedFutureDemo::Run();
    WaitForDemo::Run();
    PromiseDemo::Run();
    PromiseExceptionDemo::Run();
    DeferredDemo::Run();

    return 0;
}
