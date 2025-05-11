#include "../include/taglib_metadata_reader.hpp"

#include <taglib/mpegfile.h>
#include <taglib/id3v2tag.h>
#include <taglib/id3v2frame.h>

#include <vector>
#include <sstream>
#include <fstream>

TaglibMetadataReader::TaglibMetadataReader(const std::string& file_path)
    : file_path_(file_path) {}

std::string Utf16LeToUtf8Manual(const unsigned char* data, size_t len) {
    std::string utf8;
    for (size_t i = 0; i + 1 < len; i += 2) {
        uint16_t ch = data[i] | (data[i + 1] << 8);
        if (ch == 0x0000) break;

        if (ch <= 0x007F) {
            utf8.push_back(static_cast<char>(ch));
        } else if (ch <= 0x07FF) {
            utf8.push_back(static_cast<char>(0xC0 | ((ch >> 6) & 0x1F)));
            utf8.push_back(static_cast<char>(0x80 | (ch & 0x3F)));
        } else {
            utf8.push_back(static_cast<char>(0xE0 | ((ch >> 12) & 0x0F)));
            utf8.push_back(static_cast<char>(0x80 | ((ch >> 6) & 0x3F)));
            utf8.push_back(static_cast<char>(0x80 | (ch & 0x3F)));
        }
    }
    return utf8;
}

void TaglibMetadataReader::PrintToLog(std::shared_ptr<spdlog::logger> logger) const {
    logger->info("[TAGLIB METADATA]");
    TagLib::MPEG::File file(file_path_.c_str());

    if (!file.isValid() || !file.ID3v2Tag()) {
        logger->warn("Failed to read ID3v2 tag from: {}", file_path_);
        return;
    }

    TagLib::ID3v2::Tag* tag = file.ID3v2Tag();
    auto frames = tag->frameList("COMM");

    for (auto* frame : frames) {
        auto raw_data = frame->render();
        const unsigned char* bytes = reinterpret_cast<const unsigned char*>(raw_data.data());
        size_t size = raw_data.size();
        if (size < 16) continue;

        uint8_t encoding = bytes[10];

        if (encoding == 0x01) {  // UTF-16LE
            size_t offset = 14;
            while (offset + 1 < size && (bytes[offset] != 0x00 || bytes[offset + 1] != 0x00)) {
                offset += 2;
            }
            offset += 2;
            if (offset + 1 < size && bytes[offset] == 0xFF && bytes[offset + 1] == 0xFE) {
                offset += 2;
            }

            std::ostringstream hex_oss;
            hex_oss << "COMM payload hex from offset " << offset << ": ";
            for (size_t i = offset; i < std::min(size, offset + 32); ++i) {
                hex_oss << std::hex << (int)bytes[i] << " ";
            }
            logger->info(hex_oss.str());

            for (size_t i = 0; i + 1 < 8; i += 2) {
                char16_t ch = bytes[offset + i] | (bytes[offset + i + 1] << 8);
                logger->info("Char {}: U+{:04x}", i / 2, static_cast<uint32_t>(ch));
            }

            std::string utf8 = Utf16LeToUtf8Manual(bytes + offset, size - offset);
            logger->info("Comment (manually decoded): {}", utf8);

            // std::ofstream out("test_utf8.txt", std::ios::out | std::ios::binary);
            // if (out.is_open()) {
            //     out << utf8 << std::endl;
            //     out.close();
            //     logger->info("Wrote decoded comment to test_utf8.txt for manual inspection.");
            // }

        } else {
            logger->warn("Unsupported COMM encoding: {}", encoding);
        }
    }
}
