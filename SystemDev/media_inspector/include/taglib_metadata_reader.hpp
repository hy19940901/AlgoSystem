#ifndef TAGLIB_METADATA_READER_HPP
#define TAGLIB_METADATA_READER_HPP

#include <string>
#include <memory>
#include <spdlog/logger.h>

class TaglibMetadataReader {
public:
    explicit TaglibMetadataReader(const std::string& file_path);

    // Print metadata to provided logger (e.g., spdlog::get("taglib"))
    void print_to_log(std::shared_ptr<spdlog::logger> logger) const;

private:
    std::string file_path_;
};

#endif // TAGLIB_METADATA_READER_HPP
