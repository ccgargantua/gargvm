#include "vm_debug.h"

#include <stdio.h>
#include <stdarg.h>

void dbg_printf(const char *format, ...) {
    #ifdef DEBUG
        va_list args;
        va_start(args, format);
        fprintf(stderr, format, args);
        va_end(args);
    #else
        (void) format;
    #endif
}