#pragma once

void log_on();
void log_off();
void log_console(const char *functionname, int linenumber, const char *format,
                 ...);
