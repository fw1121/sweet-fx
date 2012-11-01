#include "seq.h"
#include <assert.h>

//---------------------------------------------------------

static char line[FX_MAXLINE];

//---------------------------------------------------------

void Seq_dump(FILE* out, Seq* s) 
{
  assert(out != NULL);
  assert(s != NULL);
  fprintf(out, "\nID\t%s", s->id);
  fprintf(out, "SEQ\t%s\n", s->seq);
  fprintf(out, "QUAL\t%s\n", s->qual);
  fprintf(out, "LEN\t%d\n", s->len);
}

//---------------------------------------------------------

int Seq_read_raw(SeqStream* ss, Seq* s) 
{
  FILE* file = ss->file[0];
  return fgets(s->seq, FX_MAXLINE, file) == NULL;
}

//---------------------------------------------------------

int Seq_read_fasta(SeqStream* ss, Seq* s) 
{
  FILE* file = ss->file[0];
  if (fgets(s->id, FX_MAXLINE, file) == NULL)
    return 1;
  if (s->id[0] != '>')
    return 1;
  return fgets(s->seq, FX_MAXLINE, file) == NULL;
}

//---------------------------------------------------------

int Seq_read_fastq(SeqStream* ss, Seq* seq)
{  
  FILE* file = ss->file[0];
  
  // 1. ID
  if (fgets(seq->id, FX_MAXLINE, file) == NULL)
    return 1;

  if (seq->id[0] != '@')
    return 2;
  
  // 2. SEQUENCE
  if (fgets(seq->seq, FX_MAXLINE, file) == NULL)
    return 3;

  // 3. ID again...
  if (fgets(line, FX_MAXLINE, file) == NULL)
    return 4;
  
  if (line[0] != '+')
    return 5;

  // 4. QUALITY
  if (fgets(seq->qual, FX_MAXLINE, file) == NULL)
    return 4;

  return 0;
}
//---------------------------------------------------------

int Seq_read(SeqStream* ss, Seq* s) 
{
  static int counter=0;
  
  // call the appropriate reader function
  int ec;
  if (ss->format == FX_FORMAT_FASTQ) {
    ec = Seq_read_fastq(ss, s);
    if (ec) return ec;
  }
  else if (ss->format == FX_FORMAT_FASTA) {
    ec = Seq_read_fasta(ss, s);
    if (ec) return ec;
  }
  else if (ss->format == FX_FORMAT_RAW) {
    ec = Seq_read_raw(ss, s);
    if (ec) return ec;
    // for raw, make an ID up
    sprintf(s->id, "#%d\n", ++counter);
  }
  else 
    return -1;
    
  // uppercase the sequence
  char *p = s->seq;
  while (*p++) {
    *p = toupper(*p);
  }  

  // pre-store length
  s->len = strlen(s->seq)-1;  
  
  // chomp \n from seq + qual
  s->seq[s->len] = '\0';
  s->qual[s->len] = '\0';
  
  // fix ID ?
  // calling strlen here is not really necessary
  // s->id[strlen(s->id)-1] = '\0';
  
  return 0;
}


//---------------------------------------------------------

int Seq_write(FILE* file, Seq* seq, int format)
{
  return fprintf(file, "%s\n%s\n+%s\n%s\n", seq->id, seq->seq, seq->id, seq->qual);
}

//---------------------------------------------------------

#define COMPLEMENT(x)  (x=='A' ? 'T' : x=='T' ? 'A' : x=='C' ? 'G' : x=='G' ? 'C' : x)

int Seq_revcom(Seq* s)
{
  Seq old = *s;
  for (int i=0; i < s->len; i++) {
    s->seq[i]  = COMPLEMENT( old.seq[s->len - i - 1] );
    s->qual[i] = old.qual[s->len - i - 1];  // quality does not 'complement'
  }
  return 0;  
}

//---------------------------------------------------------

int Seq_trim(Seq* s, int start, int end)
{
//  printf("BEFORE: id=%s len=%d start=%d end=%d\n", seq->id, seq->len, start, end);
  if (start <= 0) start = 1;
  if (end <= 0) end = s->len;
//  printf("OLD: id=%s len=%d start=%d end=%d seq=%s\n", seq->id, seq->len, start, end, seq->seq);
  
  assert(start >= 1);
  assert(end <= s->len);
/*  assert(start <= seq->len); */
  assert(end >= start);
  
  // put into "C" coordinates
  start--;
  end--;

  int newlen = end-start+1;
  for (int i=0 ; i < newlen; i++) {
    s->seq[i] = s->seq[start+i];
    s->qual[i] = s->qual[start+i];
  }
  s->seq[newlen] = s->qual[newlen] = '\0';
  s->len = newlen;

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
