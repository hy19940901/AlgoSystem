#include "../include/stream_provider.h"
#include "../include/log_config.h"

static log4cxx::LoggerPtr logger = logsys::LogConfig::getLogger("server");

void streamCallback(const char* streamData, int size) {
    if (logger->isDebugEnabled()) {
        LOG4CXX_DEBUG(logger, "StreamCallback triggered.");
    }

    LOG4CXX_INFO(logger, "Received stream data of size " << size << ". Data: " << streamData);
}

int main() {
    logsys::LogConfig::init();
    LOG4CXX_INFO(logger, "Server starting...");

    registerStreamCallback(streamCallback);
    startStream();

    LOG4CXX_INFO(logger, "Server exiting.");
    return 0;
}
