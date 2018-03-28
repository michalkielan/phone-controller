/*
 * logger.h
 *
 *  Created on: Mar 28, 2018
 *      Author: Michal Kielan
 */

#ifndef INC_LOGGER_LOGGER_H_
#define INC_LOGGER_LOGGER_H_

typedef enum
{
  LOG_ERROR,
  LOG_WARNING,
  LOG_INFO
} LogLevel;


void log_base(const LogLevel level, const char *file, const int line, const char *fmt, ...);


#define log(...) log_base(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)


#endif /* INC_LOGGER_LOGGER_H_ */
