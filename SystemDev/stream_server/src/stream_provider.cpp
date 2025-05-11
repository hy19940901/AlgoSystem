// stream_provider.cpp
#include <memory>
#include "../include/stream_provider.h"
#include "../include/stream_provider_internal.h"
#include "../include/log_config.h"

static log4cxx::LoggerPtr logger = logsys::LogConfig::get_logger("provider");

// Dynamically allocate StreamProvider using std::unique_ptr
static std::unique_ptr<StreamProvider> stream_provider(new StreamProvider());

void register_stream_callback(StreamCallback cb) {
    LOG4CXX_INFO(logger, "Registering stream callback.");
    stream_provider->register_callback(cb);
}

void start_stream() {
    LOG4CXX_INFO(logger, "Starting stream.");
    stream_provider->start_stream();
}
