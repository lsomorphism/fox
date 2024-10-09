#include "../includes/error.h"

#include <stdarg.h>
#include <stdio.h>

/*
// Note: Easier to do with a macro, like this:
#define perrorf(fmt, ...) \
   do { \
      fprintf(stderr, fmt, ##__VA_ARGS__); \
   } while(0) \

   the do-while is to make perrorf look like an actual function instead of a function-like macro 
*/

void perrorf(const char *fmt, ...) {
   va_list args; 
   va_start(args, fmt);

   // no bounds check, possible overflow 
   char msg[512];
   vsnprintf(msg, sizeof(msg), fmt, args);
   perror(msg);

   va_end(args);
}
