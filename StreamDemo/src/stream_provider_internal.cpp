// stream_provider_internal.cpp
#include <iostream>
#include <string>
#include "../include/stream_provider_internal.h"  // Include internal header

void StreamProvider::registerCallback(StreamCallback cb) {
    callback = cb;
}

void StreamProvider::startStream() {
    if (!callback) {
        std::cerr << "Error: No callback registered!" << std::endl;
        return;
    }

    // Simulate stream data
    std::string streamData = "Simulated stream data...";
    sendStreamData(streamData);
}

void StreamProvider::sendStreamData(const std::string& data) {
    int dataSize = data.size();
    std::cout << "StreamProvider: Sending stream data to server..." << std::endl;
    callback(data.c_str(), dataSize);  // Invoke the registered callback
}
