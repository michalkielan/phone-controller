/*
 * logger.c
 *
 *  Created on: Mar 28, 2018
 *      Author: Michal Kielan
 */

#include "logger/logger.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>


/**
 * @brief Array with log levels strings
 */
static const char* log_level_str[] = {"", "ERROR", "WARNING", "INFO", "VERBOSE"};


/**
 * @brief variable to set the log level, default is LOG_INFO
 */
static LogLevel log_level_max = LOG_INFO;


/**
 * @brief Get actual time for logs, this function should be implemented
 *        in bare metal using RTC
 *
 * return time structure
 */
struct tm get_actual_time()
{
  struct tm t;
  // get time from RTC in uC
  return t;
}

void set_log_level(const LogLevel level)
{
  log_level_max = level;
}

static void log_printf(const LogLevel level, const char *file, const char* function, const int line, const char *fmt, ...)
{
  if(level > log_level_max)
  {
    return;
  }

  va_list args;
  FILE* stream = stdout;

//  struct tm t = get_actual_time();
  const char* time = "00:00:00";

  fprintf(stream, "%s [%s] [%s(%s:%d)]: \t", time, log_level_str[level], file, function, line);

  va_start(args, fmt);

  vfprintf(stream, fmt, args);
  va_end(args);
  fprintf(stream, "\n");
}


void log_base(const LogLevel level, const char *file, const char* function, const int line, const char *fmt, ...)
{
#ifdef LOG_ENABLED
  log_printf(level, file, function, line, fmt);
#endif
}
