// stream_provider.cpp
#include <memory>
#include "../include/stream_provider.h"
#include "../include/stream_provider_internal.h"
#include "../include/log_config.h"

static log4cxx::LoggerPtr logger = logsys::LogConfig::GetLogger("provider");

// Dynamically allocate StreamProvider using std::unique_ptr
static std::unique_ptr<StreamProvider> stream_provider(new StreamProvider());

void RegisterStreamCallback(StreamCallback cb) {
    LOG4CXX_INFO(logger, "Registering stream callback.");
    stream_provider->RegisterCallback(cb);
}

void StartStream() {
    LOG4CXX_INFO(logger, "Starting stream.");
    stream_provider->StartStream();
}
