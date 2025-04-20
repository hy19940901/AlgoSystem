#include "../include/BoostCoreExamples.hpp"

int main() {
    BoostCoreExamples examples;

    // Core Boost usage examples
    examples.sharedPtrExample();
    examples.scopedPtrExample();
    examples.filesystemExample();
    examples.regexExample();

    // Multithreading and concurrency examples
    examples.threadExample();
    examples.threadPoolExample();
    examples.asyncCalculationExample();

    examples.programOptionsExample();
    examples.serializationExample();
    examples.coroutineExample();
    examples.interprocessExample();
    examples.lockfreeExample();
    examples.asioSocketExample();
    examples.filesystemTraverseExample();
    examples.regexReplaceExample();
    examples.boostThreadExample();

    examples.barrierExample();
    examples.latchExample();
    examples.conditionVariableExample();

    return 0;
}
