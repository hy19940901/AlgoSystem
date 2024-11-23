// ../include/server.h
#ifndef SERVER_H
#define SERVER_H

#include "../include/stream_provider.h"  // Include the stream provider interface

/**
 * @brief Server callback function to receive stream data.
 * 
 * This function is called whenever new stream data is received. It processes the data 
 * by printing the size and content to the console. This simulates the server's handling 
 * of incoming stream data.
 * 
 * @param streamData Pointer to the stream data.
 * @param size Size of the stream data in bytes.
 */
void streamCallback(const char* streamData, int size);

#endif // SERVER_H
