#define TOOL_C
#include <stdlib.h>
#include <string.h>
#include "tool.h"
#include "fx-count.h"
#include "fx-yield.h"
#include "fx-encoding.h"
#include "fx-convert.h"

//----------------------------------------------------------------------------------

Tool tool[] = {
  {
    .name   = "count",
    .desc   = "count number of reads",
    .runner = fx_count,
  },
  {
    .name   = "yield",
    .desc   = "count number of total bases",
    .runner = fx_yield,
  },
  {
    .name   = "encoding",
    .desc   = "guess the fastq quality offset",
    .runner = fx_encoding,
  },

  {
    .name = "convert",
    .desc = "convert between fastq,fasta,raw",
    .runner = fx_convert,
  },

};

const int ntool = sizeof(tool) / sizeof(tool[0]);

//----------------------------------------------------------------------------------

Tool* Tool_get(char* name) {
  for (int i=0; i < ntool; i++) {
    if (!strcmp(name, tool[i].name)) return &tool[i];
  }
  return NULL;
}

//----------------------------------------------------------------------------------

int Tool_count(void) {
  return ntool;
}

//----------------------------------------------------------------------------------


