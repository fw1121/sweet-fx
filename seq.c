#include "seq.h"
#include <assert.h>

//---------------------------------------------------------

void Seq_dump(FILE* out, Seq* s) 
{
  assert(out != NULL);
  assert(s != NULL);
  fprintf(out, "ID\t%s\n", s->id);
  fprintf(out, "SEQ\t%s\n", s->seq);
  fprintf(out, "QUAL\t%s\n", s->qual);
  fprintf(out, "LEN\t%d\n", s->len);
}

//---------------------------------------------------------

int Seq_read(SeqStream* ss, Seq* seq)
{
  static int n=0;
  static char line[FX_MAXLINE];
  
  FILE* file = ss->file[0];
  
  // 1. ID
  if (fgets(seq->id, FX_MAXLINE, file) == NULL) {
    return 1;
  }
  n++;
  if (seq->id[0] != '@') {
    fprintf(stderr, "no fastq id '@' before sequence at line %d: %s\n", n, line);
    return -1;
  }
  
  // remove \n
  seq->id[ strlen(seq->id)-1 ] = '\0';

  // 2. SEQUENCE
  if (fgets(seq->seq, FX_MAXLINE, file) == NULL) {
    return 2;
  }
  n++;

  // remove \n
  seq->len = strlen(seq->seq)-1;  
  seq->seq[seq->len] = '\0';

  // uppercase the sequence
  char *s = seq->seq;
  while (*s++) {
    *s = toupper(*s);
  }

//  return if seq->format != FX_FORMAT_FASTQ;

  // 3. ID again...
  if (fgets(line, FX_MAXLINE, file) == NULL) {
    return 3;
  }
  n++;
  if (line[0] != '+') {
    fprintf(stderr, "no fastq id '+' before quality at line %d: %s\n", n, line);
    return -3;
  }

  // 4. QUALITY
  if (fgets(seq->qual, FX_MAXLINE, file) == NULL) {
    return 4;
  }
  n++;
  seq->qual[seq->len] = '\0';  // remove \n
  
  // END OF ONE READ

  return 0;
}

//---------------------------------------------------------

int Seq_write(FILE* file, Seq* seq, int format)
{
  return fprintf(file, "%s\n%s\n+%s\n%s\n", seq->id, seq->seq, seq->id, seq->qual);
}

//---------------------------------------------------------

#define COMPLEMENT(x)  (x=='A' ? 'T' : x=='T' ? 'A' : x=='C' ? 'G' : x=='G' ? 'C' : x)

int Seq_revcom(Seq* seq)
{
  Seq old = *seq;
  for (int i=0; i < seq->len; i++) {
    seq->seq[i]  = COMPLEMENT( old.seq[seq->len - i - 1] );
    seq->qual[i] = old.qual[seq->len - i - 1];  // quality does not 'complement'
  }
  return 0;  
}

//---------------------------------------------------------

int Seq_trim(Seq* seq, int start, int end)
{
//  printf("BEFORE: id=%s len=%d start=%d end=%d\n", seq->id, seq->len, start, end);
  if (start <= 0) start = 1;
  if (end <= 0) end = seq->len;
//  printf("OLD: id=%s len=%d start=%d end=%d seq=%s\n", seq->id, seq->len, start, end, seq->seq);
  
  assert(start >= 1);
  assert(end <= seq->len);
/*  assert(start <= seq->len); */
  assert(end >= start);
  
  // put into "C" coordinates
  start--;
  end--;

  int newlen = end-start+1;
  for (int i=0 ; i < newlen; i++) {
    seq->seq[i] = seq->seq[start+i];
    seq->qual[i] = seq->qual[start+i];
  }
  seq->seq[newlen] = seq->qual[newlen] = '\0';
  seq->len = newlen;

//  printf("NEW: id=%s len=%d start=%d end=%d seq=%s\n", seq->id, seq->len, start, end, seq->seq);

/*
  memmove(seq->seq, &(seq->seq[start]), newlen*sizeof(char));
  seq->seq[newlen] = '\0';
  memmove(seq->qual, &(seq->qual[start]), newlen*sizeof(char));
  seq->qual[newlen] = '\0';
  seq->len = newlen;
*/

  return newlen;
}
