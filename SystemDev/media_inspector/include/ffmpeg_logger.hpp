#ifndef FFMPEG_LOGGER_HPP
#define FFMPEG_LOGGER_HPP

#include <memory>
#include <spdlog/spdlog.h>

/**
 * @brief Registers a custom log callback to redirect FFmpeg internal logs to spdlog.
 * 
 * This function installs a callback using av_log_set_callback to capture FFmpeg logs
 * and forward them to a given spdlog logger with appropriate severity levels.
 * 
 * @param logger A shared pointer to the spdlog logger instance that will receive FFmpeg logs.
 */
void RegisterFfmpegLogCallback(std::shared_ptr<spdlog::logger> logger);

#endif // FFMPEG_LOGGER_HPP
