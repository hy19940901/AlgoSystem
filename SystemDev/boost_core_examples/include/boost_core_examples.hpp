#ifndef BOOST_CORE_EXAMPLES_HPP
#define BOOST_CORE_EXAMPLES_HPP

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <boost/program_options.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/coroutine2/all.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/thread/barrier.hpp>
#include <boost/thread/latch.hpp>
#include <boost/thread/condition_variable.hpp>

#include <string>
#include <atomic>
#include <future>
#include <queue>

/**
 * @brief A class demonstrating various Boost library components and concurrency mechanisms.
 */
class BoostCoreExamples {
public:
    BoostCoreExamples();

    // === Smart Pointer Examples ===
    void SharedPtrExample();           
    void ScopedPtrExample();           

    // === Filesystem and Regex ===
    void FilesystemExample();          
    void RegexExample();               
    void RegexReplaceExample();        
    void FilesystemTraverseExample();  

    // === Threading and Task Execution ===
    void ThreadExample();              
    void ThreadPoolExample();          
    void AsyncCalculationExample();    

    // === Command Line / Serialization / Coroutine ===
    void ProgramOptionsExample();      
    void SerializationExample();       
    void CoroutineExample();           

    // === Interprocess & Lockfree Queue ===
    void InterprocessExample();        
    void LockfreeExample();            

    // === Networking ===
    void AsioSocketExample();          

    // === Boost Threads ===
    void BoostThreadExample();         
    void BarrierExample();             
    void LatchExample();               
    void ConditionVariableExample();   

    // === Helper Methods ===
    void ExecuteTask(int task_id, std::atomic<int>& completed_tasks);  
    int SimpleCalculation(int task_id);     
    int ComplexCalculation(int task_id);    
};

#endif // BOOST_CORE_EXAMPLES_HPP
