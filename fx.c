#include <math.h>
#include <getopt.h>
#include "fx.h"

//---------------------------------------------------------

void usage(void) {
  fprintf(stderr,"SYNOPSIS\n  SweetFX: Fast NGS read file tools <torsten.seemann@monash.edu>\n");
  fprintf(stderr,"USAGE\n  fx <tool> [options] <inputs>\n");
  fprintf(stderr,"TOOLS\n  FIXME\n");
  fprintf(stderr,"OPTIONS\n");
  fprintf(stderr,"  -q    FASTQ quality encoding offset (33=Sanger, 59=Solexa, 64=Illumina)\n");
}

//---------------------------------------------------------

int main(int argc, char* argv[]) 
{
  


  int qzero=33;

  while (1) {
    int c = getopt(argc, argv, "hq:");
    if (c == -1) break;
    switch (c) {
      case 'h':
        usage();
        exit(0);
      case 'q':
        qzero = atoi(optarg);
	message("Setting qzero=%d", qzero);
	break;
      default:
        error("%s: unknown option '%c'", argv[0], c);
    }
  }


  int narg = argc-optind;  
  if (narg != 1) {
    error("Please specify a tool, eg. fx count", narg);
  }
  
  message("Opening: %s", argv[optind]);
  
  SeqStream ss = SeqStream_open_single(argv[optind]);
  SeqStream_dump(stderr, &ss);
  Seq s;
  
  while ( Seq_read(&ss, &s) == 0 ) {
    Seq_dump(stdout, &s);
  }
  

  
  return 0;
}

//---------------------------------------------------------

