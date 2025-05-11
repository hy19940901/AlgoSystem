#include "../include/boost_core_examples.hpp"

int main() {
    BoostCoreExamples examples;

    examples.SharedPtrExample();
    examples.ScopedPtrExample();
    examples.FilesystemExample();
    examples.RegexExample();
    examples.ThreadExample();
    examples.ThreadPoolExample();
    examples.AsyncCalculationExample();
    examples.ProgramOptionsExample();
    examples.SerializationExample();
    examples.CoroutineExample();
    examples.InterprocessExample();
    examples.LockfreeExample();
    examples.AsioSocketExample();
    examples.FilesystemTraverseExample();
    examples.RegexReplaceExample();
    examples.BoostThreadExample();
    examples.BarrierExample();
    examples.LatchExample();
    examples.ConditionVariableExample();

    return 0;
}
