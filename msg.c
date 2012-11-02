#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>

//--------------------------------------------------------------------------

static time_t epoch = 0;

//--------------------------------------------------------------------------

void msg(char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  if (!epoch) epoch = time(NULL);
  time_t tick = time(NULL) - epoch;
  fprintf(stderr, "[%ld] ", tick);
  vfprintf(stderr, fmt, args);
  va_end(args);
  fprintf(stderr, "\n");
}


//--------------------------------------------------------------------------

void _warning(char* fmt, ...)
{
  va_list args;
  msg(fmt, args);
}

//--------------------------------------------------------------------------

void _error(char* fmt, ...)
{
  va_list args;
  msg(fmt, args);
  exit(-1);
}

//--------------------------------------------------------------------------