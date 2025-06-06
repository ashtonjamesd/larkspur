#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#include "logger.h"
#include "result.h"

static void log_message(Logger logger, char *type, const char *fmt, va_list args) {
    FILE *fptr = fopen(logger.log_directory, "a");
    if (!fptr) return;

    fprintf(fptr, "%s", type);
    fprintf(fptr, "[%u]: ", (unsigned)time(NULL));
    vfprintf(fptr, fmt, args);
    fprintf(fptr, "\n");

    fclose(fptr);
}

void log_info(Logger logger, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    log_message(logger, "[INFO]", fmt, args);
    va_end(args);
}

void log_warning(Logger logger, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    log_message(logger, "[WARNING]", fmt, args);
    va_end(args);
}

void log_error(Logger logger, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    log_message(logger, "[ERROR]", fmt, args);
    va_end(args);
}

LarkspurResult log_error_result(Logger logger, LarkspurResult result) {
    log_error(logger, "%s", result_to_str(result));
    return result;
}