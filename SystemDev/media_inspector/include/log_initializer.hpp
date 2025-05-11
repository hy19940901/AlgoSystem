#ifndef LOG_INITIALIZER_HPP
#define LOG_INITIALIZER_HPP

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/logger.h>
#include <memory>
#include <string>

namespace log_initializer {

// Initializes all loggers and sinks.
void Init();

// Returns a named logger.
std::shared_ptr<spdlog::logger> GetLogger(const std::string& name);

// Sets the global log level.
void SetLevel(spdlog::level::level_enum level);

// Disables console output for all loggers.
void DisableConsoleOutput();

}  // namespace log_initializer

#endif // LOG_INITIALIZER_HPP
