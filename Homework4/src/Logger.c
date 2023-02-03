#include "Logger.h"

#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include <stdbool.h>

static bool log_enable = false;

void log_on()
{
  log_enable = true;
}
void log_off()
{
  log_enable = false;
}

void log_console(const char *functionname, int linenumber, const char *format,
                 ...)
{
  if (log_enable)
  {
    fprintf(stdout, "[%s, %i]: ", functionname, linenumber);
    va_list args;

    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);
    fprintf(stdout, "\n");
  }
}
