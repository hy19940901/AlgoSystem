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
void init();

// Returns a named logger.
std::shared_ptr<spdlog::logger> get_logger(const std::string& name);

// Sets the global log level.
void set_level(spdlog::level::level_enum level);

// Disables console output for all loggers.
void disable_console_output();

}  // namespace log_initializer

#endif // LOG_INITIALIZER_HPP
