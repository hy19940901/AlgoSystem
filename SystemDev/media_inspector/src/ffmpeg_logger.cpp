#include "../include/ffmpeg_logger.hpp"

extern "C" {
#include <libavutil/log.h>
}

#include <mutex>

static std::shared_ptr<spdlog::logger> ffmpeg_logger;
static std::mutex logger_mutex;

extern "C" void FfmpegLogCallback(void* /*ptr*/, int level, const char* fmt, va_list vl) {
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), fmt, vl);

    if (buffer[0] == '\0' || (buffer[0] == '\n' && buffer[1] == '\0')) {
        return;
    }

    std::shared_ptr<spdlog::logger> logger_copy;
    {
        std::lock_guard<std::mutex> lock(logger_mutex);
        logger_copy = ffmpeg_logger;
    }

    if (!logger_copy) return;

    switch (level) {
        case AV_LOG_PANIC:
        case AV_LOG_FATAL:
        case AV_LOG_ERROR:
            logger_copy->error("[ffmpeg] {}", buffer);
            break;
        case AV_LOG_WARNING:
            logger_copy->warn("[ffmpeg] {}", buffer);
            break;
        case AV_LOG_INFO:
        case AV_LOG_VERBOSE:
            logger_copy->info("[ffmpeg] {}", buffer);
            break;
        case AV_LOG_DEBUG:
            logger_copy->debug("[ffmpeg] {}", buffer);
            break;
        default:
            logger_copy->trace("[ffmpeg] {}", buffer);
            break;
    }
}

void RegisterFfmpegLogCallback(std::shared_ptr<spdlog::logger> logger) {
    std::lock_guard<std::mutex> lock(logger_mutex);
    ffmpeg_logger = std::move(logger);

    // 1. Register your callback first
    av_log_set_callback(FfmpegLogCallback);

    // 2. Set FFmpeg log level high enough to capture logs (e.g., INFO)
    av_log_set_level(AV_LOG_INFO);
}