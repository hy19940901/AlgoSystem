#ifndef BOOST_CORE_EXAMPLES_HPP
#define BOOST_CORE_EXAMPLES_HPP

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <atomic>
#include <chrono>
#include <functional>
#include <thread>
#include <future>
#include <vector>

class BoostCoreExamples {
public:
    BoostCoreExamples();

    void sharedPtrExample();
    void scopedPtrExample();
    void filesystemExample();
    void regexExample();
    void threadExample();
    void threadPoolExample();
    void asyncCalculationExample();

private:
    int simple_calculation(int task_id);
    int complex_calculation(int task_id);
    void executeTask(int task_id, std::atomic<int>& completed_tasks);
};

#endif // BOOST_CORE_EXAMPLES_HPP
