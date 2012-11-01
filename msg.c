#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>

//--------------------------------------------------------------------------

static time_t epoch = 0;

//--------------------------------------------------------------------------

void message(char* fmt, ...)
{
  va_list args;
  if (!epoch) epoch = time(NULL);
  time_t tick = time(NULL) - epoch;
  fprintf(stderr, "[%ld] ", tick);
  fprintf(stderr, fmt, args);
  fprintf(stderr, "\n");
}


//--------------------------------------------------------------------------

void warning(char* fmt, ...)
{
  va_list args;
  message(fmt, args);
}


//--------------------------------------------------------------------------

void error(char* fmt, ...)
{
  va_list args;
  message(fmt, args);
  exit(-1);
}

//--------------------------------------------------------------------------
