#ifndef SEQSTREAM_H
#define SEQSTREAM_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

#define FX_FORMAT_FASTQ		1
#define FX_FORMAT_FASTA		2
#define FX_FORMAT_RAW		3

#define FX_TYPE_SINGLE		1
#define FX_TYPE_INTERLEAVED	2
#define FX_TYPE_PAIRED		3

typedef struct SeqStream {
  FILE* file[2];
  int   type;
  int   format;
}
SeqStream;

void SeqStream_dump(FILE* out, SeqStream* ss);

SeqStream SeqStream_open(char* f1, char* f2, int type);

SeqStream SeqStream_open_single(char *fname);
SeqStream SeqStream_open_interleaved(char *fname);
SeqStream SeqStream_open_paired(char *left, char* right);

#endif
