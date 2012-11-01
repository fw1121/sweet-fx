#include <math.h>
#include <getopt.h>
#include "fx.h"

//---------------------------------------------------------

int main(int argc, char* argv[]) 
{
//  SeqStream in;
//  Seq read;
  int qzero=33;
  
  while (1) {
    int c = getopt(argc, argv, "ho:");
    if (c == -1) break;
    switch (c) {
      case 'h':
        HELP:
        fprintf(stderr,"Usage: %s [options] file.fastq [file2.fq ...]\n", argv[0]);
	fprintf(stderr,"\t-h\tshow this help\n");       
	fprintf(stderr,"\t-q Q0\tfastq offset: sanger=33 solexa=59 illumina=64 (default=33)\n");
        exit(0);
      case 'q':
        qzero = atoi(optarg);
	fprintf(stderr, "Setting qzero=%d\n", qzero);
	break;
      default:
        fprintf(stderr, "%s: unknown option '%c'\n", argv[0], c);
	exit(-1);
    }
  }

//  goto HELP;

  int narg = argc-optind;  
  if (narg != 1) {
    fprintf(stderr, "A FASTQ filename arguments are required - you supplied %d.\n", narg);
    exit(1);
  }
  
  fprintf(stderr, "Opening: %s\n", argv[optind]);
  
  SeqStream ss = SeqStream_open_single(argv[optind]);
  SeqStream_dump(stderr, &ss);
  Seq s;
  
  while ( Seq_read(&ss, &s) == 0 ) {
    Seq_dump(stdout, &s);
  }
  

  
  return 0;
}

//---------------------------------------------------------

