#include "../include/mp3_info.h"
#include <iostream>
#include <fstream>
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}

/**
 * @brief Extracts stream and lyrics information from the given MP3 file.
 * @param filename The input MP3 file name.
 */
void extract_stream_info(const std::string& filename) {
    AVFormatContext* formatContext = nullptr;

    // Open the input file
    if (avformat_open_input(&formatContext, filename.c_str(), nullptr, nullptr) < 0) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    // Retrieve stream information
    if (avformat_find_stream_info(formatContext, nullptr) < 0) {
        std::cerr << "Failed to retrieve stream info" << std::endl;
        avformat_close_input(&formatContext);
        return;
    }

    // Print stream information
    av_dump_format(formatContext, 0, filename.c_str(), 0);

    // Extract metadata (e.g., lyrics)
    AVDictionary* metadata = formatContext->metadata;
    if (metadata) {
        std::ofstream lyricsFile("lyrics.txt");
        if (!lyricsFile.is_open()) {
            std::cerr << "Failed to open output file for lyrics" << std::endl;
            avformat_close_input(&formatContext);
            return;
        }

        AVDictionaryEntry* entry = nullptr;
        while ((entry = av_dict_get(metadata, "", entry, AV_DICT_IGNORE_SUFFIX))) {
            if (std::string(entry->key).find("lyrics") != std::string::npos) {
                lyricsFile << entry->value << std::endl;
            }
        }

        lyricsFile.close();
        std::cout << "Lyrics extracted to 'lyrics.txt'." << std::endl;
    } else {
        std::cout << "No metadata (lyrics) found in file: " << filename << std::endl;
    }

    // Release resources
    avformat_close_input(&formatContext);
}
