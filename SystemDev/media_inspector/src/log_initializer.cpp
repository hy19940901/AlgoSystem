#include "../include/log_initializer.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/spdlog.h>

#include <memory>
#include <vector>
#include <mutex>
#include <iostream>

namespace log_initializer {

namespace {

std::shared_ptr<spdlog::logger> global_logger;
std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> console_sink;
std::once_flag init_flag;

}  // namespace

void init() {
    std::call_once(init_flag, [] {
        try {
            auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
                "logs/media_inspector.log", true);

            auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
                "logs/media_inspector_rotating.log", 1024 * 1024 * 5, 3);  // 5MB, keep 3 files

            std::vector<spdlog::sink_ptr> sinks{file_sink, rotating_sink};

            global_logger = std::make_shared<spdlog::logger>("default_logger", sinks.begin(), sinks.end());

            spdlog::set_default_logger(global_logger);
            spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] [%n] %v");
            spdlog::set_level(spdlog::level::info);

        } catch (const spdlog::spdlog_ex& ex) {
            std::cerr << "Log initialization failed: " << ex.what() << std::endl;
        }
    });
}

std::shared_ptr<spdlog::logger> get_logger() {
    return global_logger;
}

void set_level(spdlog::level::level_enum level) {
    if (global_logger) {
        global_logger->set_level(level);
    }
}

void disable_console_output() {
    if (console_sink) {
        console_sink->set_level(spdlog::level::off);
    }
}

}  // namespace log_initializer
