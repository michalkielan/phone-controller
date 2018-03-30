/*
 * logger.h
 *
 *  Created on: Mar 28, 2018
 *      Author: Michal Kielan
 */

#ifndef INC_LOGGER_LOGGER_H_
#define INC_LOGGER_LOGGER_H_


/**
 * @brief Log levels types
 */
typedef enum
{
  LOG_NONE,
  LOG_ERROR,
  LOG_WARNING,
  LOG_INFO,
  LOG_VERBOSE
} LogLevel;


/**
 * @brief This is the base function for printing logs, should not be called by hand,
 *        the macro 'LOGF' must be used instead. The macro 'LOG_ENABLED' should
 *        be set to see the output logs.
 *
 * \param [in] log level enumerated type
 * \param [in] file name
 * \param [in] function name
 * \param [in] line number
 * \param [in] fmt, format variadic argument
 *
 */
void log_base(const LogLevel level, const char *file, const char* function, const int line, const char *fmt, ...);


/**
 * @brief Set the log level, every logs with level lower than
 *        the input will be ignored, the default level is 'LOG_INFO'
 *
 *  \param [in] log level
 */
void set_log_level(const LogLevel level);


/**
 * @brief Log format - this is the user interface function-macro for logger,
 *        the output format is: [time] [log level] [file] [function:line] [log message]
 *        00:00:00 [ERROR] [path/to/file.c(crypt_xor:20)]: log message
 *        Use it like printf function, and type log level as a first parameter
 *
 *
 * \param [in] log level enumerated type
 * \param [in] format variadic argument
 *
 */
#define LOGF(LOG_LEVEL, ...) log_base(LOG_LEVEL, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)


#endif /* INC_LOGGER_LOGGER_H_ */
