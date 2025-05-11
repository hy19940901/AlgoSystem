#ifndef FFMPEG_HANDLER_HPP
#define FFMPEG_HANDLER_HPP

#include <string>
#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/logger.h>

class FfmpegHandler {
public:
    explicit FfmpegHandler(const std::string& path);
    ~FfmpegHandler();

    bool Open();
    void PrintMediaInfo() const;

private:
    void PrintAudioInfo(void* stream) const;
    std::string file_path_;
    void* format_ctx_;
};

#endif // FFMPEG_HANDLER_HPP
