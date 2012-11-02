#define TOOL_C
#include <stdlib.h>
#include "tool.h"

//----------------------------------------------------------------------------------

const Tool tool[] = {
  {
    .name = "count",
    .desc = "count number of reads",
  },
  {
    .name = "yield",
    .desc = "count number of total bases",
  },
  {
    .name = "encoding",
    .desc = "guess the fastq quality offset",
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

int Tool_run(Tool* tool) {
  return 0;
}

//----------------------------------------------------------------------------------


