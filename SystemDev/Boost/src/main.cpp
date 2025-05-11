#include "../include/boost_core_examples.hpp"

int main() {
    BoostCoreExamples examples;

    examples.shared_ptr_example();
    examples.scoped_ptr_example();
    examples.filesystem_example();
    examples.regex_example();
    examples.thread_example();
    examples.thread_pool_example();
    examples.async_calculation_example();
    examples.program_options_example();
    examples.serialization_example();
    examples.coroutine_example();
    examples.interprocess_example();
    examples.lockfree_example();
    examples.asio_socket_example();
    examples.filesystem_traverse_example();
    examples.regex_replace_example();
    examples.boost_thread_example();
    examples.barrier_example();
    examples.latch_example();
    examples.condition_variable_example();

    return 0;
}
