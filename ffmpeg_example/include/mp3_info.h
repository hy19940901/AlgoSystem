#ifndef MP3_INFO_H
#define MP3_INFO_H

#include <string>

/**
 * @brief Extracts stream and subtitle information from the given file.
 * @param filename The input file name.
 */
void extract_stream_info(const std::string& filename);

#endif // MP3_INFO_H
