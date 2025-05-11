#include "../include/stream_provider.h"
#include "../include/log_config.h"

static log4cxx::LoggerPtr logger = logsys::LogConfig::GetLogger("server");

void StreamDataCallback(const char* stream_data, int size) {
    if (logger->isDebugEnabled()) {
        LOG4CXX_DEBUG(logger, "stream_callback triggered.");
    }

    LOG4CXX_INFO(logger, "Received stream data of size " << size << ". Data: " << stream_data);
}

int main() {
    logsys::LogConfig::Init();
    LOG4CXX_INFO(logger, "Server starting...");

    RegisterStreamCallback(StreamDataCallback);
    StartStream();

    LOG4CXX_INFO(logger, "Server exiting.");
    return 0;
}

