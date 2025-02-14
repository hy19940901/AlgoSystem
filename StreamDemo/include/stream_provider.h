// ../include/stream_provider.h
#ifndef STREAM_PROVIDER_H
#define STREAM_PROVIDER_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Type definition for the stream callback function.
 *
 * This callback function is used to send stream data from the internal
 * implementation to the external user. The callback takes two parameters:
 * - `streamData`: A pointer to a character array containing the stream data.
 * - `size`: The size of the data being passed to the callback.
 */
typedef void (*StreamCallback)(const char* streamData, int size);

/**
 * @brief Registers a callback function for stream data.
 *
 * This function allows the user to register a callback function that will be
 * used by the internal streaming implementation to pass data back to the user.
 * Only one callback can be registered at a time; subsequent calls will overwrite
 * the previously registered callback.
 *
 * @param cb A function pointer to the user-defined callback function that conforms
 *           to the StreamCallback type.
 */
void registerStreamCallback(StreamCallback cb);

/**
 * @brief Starts the stream and uses the registered callback to pass data.
 *
 * This function initiates the streaming process. If a callback has been registered,
 * the function will generate stream data and pass it to the registered callback. If no
 * callback has been registered, an error message will be logged.
 */
void startStream();

#ifdef __cplusplus
}
#endif

#endif // STREAM_PROVIDER_H
