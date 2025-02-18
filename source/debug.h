#ifndef DEBUG_H
#define DEBUG_H


#include <stdarg.h>
#include <stdio.h>


#ifndef NDEBUG

    static inline void dbg_printf(const char *format, ...)
    {
        va_list args;
        va_start(args, format);
        vfprintf(stderr, format, args);
        va_end(args);
    }

#else

    static inline void dbg_printf(const char *format, ...) {}

#endif



#endif