#include <math.h>
#include <getopt.h>
#include "fx.h"

//---------------------------------------------------------

void usage(void) {
  fprintf(stderr,"SYNOPSIS\n  SweetFX: Fast NGS read file tools\n");
  fprintf(stderr,"USAGE\n  fx <tool> [options]\n");
  fprintf(stderr,"TOOLS\n");
  for (int i=0; i < ntool; i++) {
    fprintf(stderr,"  %-10s  %s\n", tool[i].name, tool[i].desc);
  }
  fprintf(stderr,"SEE ALSO\n  https://github.com/Victorian-Bioinformatics-Consortium/sweet-fx\n");
  /*
  fprintf(stderr,"SHARED OPTIONS\n");
  fprintf(stderr,"  -Q    fastq offset: 33=Sanger 59=Solexa 64=Illumina\n");
  fprintf(stderr,"  -v    verbose output\n");
  fprintf(stderr,"  -t    number of threads\n");
  */
}

//---------------------------------------------------------

int main(int argc, char* argv[]) 
{
  if (argc < 2) {
    usage();
    exit(EXIT_FAILURE);
  }
  
  Tool* tool = Tool_get(argv[1]);
  if (tool == NULL) {
    msg("'%s' is not a valid tool", argv[1]);
    exit(EXIT_FAILURE);
  }
  
  (tool->runner)(argc-1, argv+1);
  
  return 0;
}

//---------------------------------------------------------

