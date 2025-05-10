// stream_provider.cpp
#include <memory>
#include "../include/stream_provider.h"
#include "../include/stream_provider_internal.h"
#include "../include/log_config.h"

static log4cxx::LoggerPtr logger = logsys::LogConfig::getLogger("provider");

// Dynamically allocate StreamProvider using std::unique_ptr
static std::unique_ptr<StreamProvider> streamProvider(new StreamProvider());

void registerStreamCallback(StreamCallback cb) {
    LOG4CXX_INFO(logger, "Registering stream callback.");
    streamProvider->registerCallback(cb);
}

void startStream() {
    LOG4CXX_INFO(logger, "Starting stream.");
    streamProvider->startStream();
}
