#ifndef LOGGER_H
#define LOGGER_H

#include "result.h"

typedef struct {
    char *log_directory;
} Logger;

void           log_info(Logger logger, const char *fmt, ...);
void           log_warning(Logger logger, const char *fmt, ...);
void           log_error(Logger logger, const char *fmt, ...);
LarkspurResult log_error_result(Logger logger, LarkspurResult result);
#endif