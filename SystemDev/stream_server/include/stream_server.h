// ../include/server.h
#ifndef STREAM_SERVER_H
#define STREAM_SERVER_H

#include "../include/stream_provider.h"  // Include the stream provider interface

/**
 * @brief Server callback function to receive stream data.
 *
 * This function is called whenever new stream data is received. It processes the data
 * by printing the size and content to the console. This simulates the server's handling
 * of incoming stream data.
 *
 * @param stream_data Pointer to the stream data.
 * @param size Size of the stream data in bytes.
 */
void stream_callback(const char* stream_data, int size);

#endif // STREAM_SERVER_H
