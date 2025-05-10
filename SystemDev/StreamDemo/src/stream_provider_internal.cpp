#include "../include/stream_provider_internal.h"
#include "../include/log_config.h"
#include <cstring>

static log4cxx::LoggerPtr logger = logsys::LogConfig::getLogger("provider_internal");

void StreamProvider::registerCallback(StreamCallback cb) {
    LOG4CXX_INFO(logger, "Callback registered.");
    callback = cb;
}

void StreamProvider::startStream() {
    if (!callback) {
        LOG4CXX_ERROR(logger, "No callback registered! Cannot send data.");
        return;
    }

    const char* message = "Simulated stream data...";
    char* streamData = new char[strlen(message) + 1];
    std::strcpy(streamData, message);

    if (logger->isDebugEnabled()) {
        LOG4CXX_DEBUG(logger, "Sending stream data to callback...");
    }

    callback(streamData, strlen(streamData));

    delete[] streamData;
}
