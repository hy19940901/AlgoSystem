#include "../include/stream_provider_internal.h"
#include "../include/log_config.h"
#include <cstring>

static log4cxx::LoggerPtr logger = logsys::LogConfig::get_logger("provider_internal");

void StreamProvider::register_callback(StreamCallback cb) {
    LOG4CXX_INFO(logger, "Callback registered.");
    callback_ = cb;
}

void StreamProvider::start_stream() {
    if (!callback_) {
        LOG4CXX_ERROR(logger, "No callback registered! Cannot send data.");
        return;
    }

    const char* message = "Simulated stream data...";
    char* stream_data = new char[strlen(message) + 1];
    std::strcpy(stream_data, message);

    if (logger->isDebugEnabled()) {
        LOG4CXX_DEBUG(logger, "Sending stream data to callback...");
    }

    callback_(stream_data, strlen(stream_data));
    delete[] stream_data;
}