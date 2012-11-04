#include "fx.h"

int fx_count(int argc, char* argv[])
{
  long count=0;
  for (int i=1; i < argc; i++) {
    msg("Reading: %s", argv[i]);
    SeqStream ss = SeqStream_open_single(argv[i]);
    Seq s;
    while (!Seq_read(&ss, &s)) {
      count++;
    }
  }
  printf("%ld\n", count);
  return 0;
}

