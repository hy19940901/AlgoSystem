#ifndef LOG_CONFIG_H
#define LOG_CONFIG_H

#include <log4cxx/logger.h>
#include <string>

namespace logsys {

/**
 * @brief A simple static class to configure and retrieve log4cxx loggers.
 */
class LogConfig {
public:
    /**
     * @brief Initialize the logging system.
     *        Uses BasicConfigurator by default. Replaceable with config file later.
     */
    static void init();

    /**
     * @brief Get a logger by name.
     * @param name The name of the logger.
     * @return A log4cxx::LoggerPtr to use for logging.
     */
    static log4cxx::LoggerPtr getLogger(const std::string& name);
};

} // namespace logsys

#endif // LOG_CONFIG_H
