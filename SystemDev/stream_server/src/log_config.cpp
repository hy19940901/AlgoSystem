#include "../include/log_config.h"
#include <log4cxx/propertyconfigurator.h>
#include <iostream>

using namespace log4cxx;

namespace logsys {

/**
 * @brief Initialize the log4cxx logging system.
 *        It loads the configuration from a file named "log4cxx.properties"
 *        located in the current working directory (usually project root).
 */
void LogConfig::init() {
    try {
        PropertyConfigurator::configure("log4cxx.properties");
    } catch (const std::exception& e) {
        std::cerr << "Failed to load log4cxx configuration: " << e.what() << std::endl;
    }
}

/**
 * @brief Retrieve a logger by name.
 * @param name The name of the logger (e.g. "server", "provider").
 * @return A logger instance to use with LOG4CXX_INFO, etc.
 */
LoggerPtr LogConfig::get_logger(const std::string& name) {
    return Logger::getLogger(name);
}

}  // namespace logsys
