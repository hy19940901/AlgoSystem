// server.cpp
#include <iostream>
#include "../include/server.h"  // Include the header file

void streamCallback(const char* streamData, int size) {
    std::cout << "Server: Received stream data of size " << size 
              << ". Data: " << streamData << std::endl;
}

int main() {
    // Register the callback function to handle stream data
    registerStreamCallback(streamCallback);

    // Start the stream (triggers the callback)
    startStream();

    return 0;
}
