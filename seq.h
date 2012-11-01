#ifndef SEQ_H
#define SEQ_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

#include "seqstream.h"

#define FX_MAXLINE	(1 << 10)

typedef struct Seq {
  char id[FX_MAXLINE];
  char seq[FX_MAXLINE];
  char qual[FX_MAXLINE];
  int  len;
} 
Seq;

void Seq_dump(FILE* out, Seq* s);
int Seq_read(SeqStream* ss, Seq* s);
//int Seq_write(SeqStream* ss, Seq* seq);
int Seq_revcom(Seq* s);
int Seq_trim(Seq* s, int start, int end);

#endif
