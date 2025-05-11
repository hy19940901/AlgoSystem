// ../include/stream_provider_internal.h
#ifndef STREAM_PROVIDER_INTERNAL_H
#define STREAM_PROVIDER_INTERNAL_H

#include <string>
#include "stream_provider.h"  // Include the public header for StreamCallback

/**
 * @class StreamProvider
 * @brief Internal class responsible for handling stream data.
 */
class StreamProvider {
public:
    // Registers the callback function for stream data
    void register_callback(StreamCallback cb);

    // Starts the streaming process
    void start_stream();

private:
    StreamCallback callback_ = nullptr;  // Stores the callback function

    // Internal method to send stream data using the callback
    void send_stream_data(const std::string& data);
};

#endif // STREAM_PROVIDER_INTERNAL_H
