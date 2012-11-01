#include <assert.h>
#include "seqstream.h"

//---------------------------------------------------------

const char* typeName[] = {
  "ERROR",
  "single",
  "interleaved",
  "paired",
};

const char* formatName[] = {
  "ERROR", 
  "fastq",
  "fasta",
  "raw",
};

//---------------------------------------------------------

void SeqStream_dump(FILE* out, SeqStream* ss) 
{
  assert(out != NULL);
  assert(ss != NULL);
  fprintf(out, "TYPE\t%d (%s)\n", ss->type, typeName[ss->type]);
  fprintf(out, "FORMAT\t%d (%s)\n", ss->format, formatName[ss->format]);
  fprintf(out, "FILE1\t%p\n",  (void*) ss->file[0]);
  fprintf(out, "FILE2\t%p\n",  (void*) ss->file[1]);
}

//---------------------------------------------------------

SeqStream SeqStream_open(char* f1, char* f2, int type)
{
  assert(f1 != NULL);
  assert(type==FX_TYPE_SINGLE || type==FX_TYPE_PAIRED || type==FX_TYPE_INTERLEAVED);

  SeqStream ss;
  
  ss.type = type;
  ss.format = 0;
  ss.file[0] = NULL;
  ss.file[1] = NULL;
  
  ss.file[0] = fopen(f1, "rw");
  assert(ss.file[0] != NULL);
  
  if (ss.type == FX_TYPE_PAIRED) {
    assert(f2 != NULL);
    ss.file[1] = fopen(f2, "rw");
    assert(ss.file[1] != NULL);
  }
  
  // Try and guess the file format
  int peek = getc(ss.file[0]);
  ungetc(peek, ss.file[0]);
  ss.format = peek=='@' ? FX_FORMAT_FASTQ : peek=='>' ? FX_FORMAT_FASTA : FX_FORMAT_RAW ;  
    
  return ss;    
}

//---------------------------------------------------------

SeqStream SeqStream_open_single(char *f1)
{
  return SeqStream_open(f1, NULL, FX_TYPE_SINGLE);
}

//---------------------------------------------------------

SeqStream SeqStream_open_interleaved(char *f1)
{
  return SeqStream_open(f1, NULL, FX_TYPE_INTERLEAVED);
}

//---------------------------------------------------------

SeqStream SeqStream_open_paired(char *left, char* right)
{
  return SeqStream_open(left, right, FX_TYPE_PAIRED);
}

//---------------------------------------------------------
