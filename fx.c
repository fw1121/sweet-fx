#include <math.h>
#include <getopt.h>
#include "fx.h"

//---------------------------------------------------------

void usage(void) {
  fprintf(stderr,"SYNOPSIS\n  SweetFX: Fast NGS read file tools <torsten.seemann@monash.edu>\n");
  fprintf(stderr,"USAGE\n  fx <tool> [options] <inputs>\n");
  fprintf(stderr,"TOOLS\n");
  for (int i=0; i < ntool; i++) {
    fprintf(stderr,"  %-10s  %s\n", tool[i].name, tool[i].desc);
  }
  fprintf(stderr,"SHARED OPTIONS\n");
  fprintf(stderr,"  -Q    fastq offset: 33=Sanger 59=Solexa 64=Illumina\n");
  fprintf(stderr,"  -v    verbose output\n");
  fprintf(stderr,"  -t    number of threads\n");
}

//---------------------------------------------------------

int main(int argc, char* argv[]) 
{
  msg("argc=%d", argc);
  msg("argv[1]=%s", argv[1]);
  if (argc < 2) {
    usage();
    msg("Please specify a valid tool");
    exit(EXIT_FAILURE);
  }
  
  Tool* tool = Tool_get(argv[1]);
  if (tool == NULL) {
    msg("'%s' is not a valid tool", argv[1]);
    exit(EXIT_FAILURE);
  }
  msg("Selected tool '%s'", tool->name);

  // options
  int qzero=33;
  int verbose=0;
  int nthread=1;

  while (1) {
    int c = getopt(argc-1, argv+1, "hvQ:t:");
    if (c == -1) break;
    switch (c) {
      case 'h':
        usage();
        exit(0);
      case 'Q':
        qzero = atoi(optarg);
        assert(qzero >= 33);
	break;
      case 't':
        nthread = atoi(optarg);
        assert(nthread > 0);
	break;
      case 'v':
        verbose++;
	break;
      default:
        msg("%s: unknown option '%c'", argv[0], c);
        exit(EXIT_FAILURE);
    }
  }

  int narg = argc-optind;  
  
  msg("Opening: %s", argv[optind]);
  
  SeqStream ss = SeqStream_open_single(argv[optind]);
  SeqStream_dump(stderr, &ss);
  Seq s;
  
  while ( Seq_read(&ss, &s) == 0 ) {
    Seq_dump(stdout, &s);
  }
  

  
  return 0;
}

//---------------------------------------------------------

