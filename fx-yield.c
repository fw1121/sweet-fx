#include "fx.h"

int fx_yield(int argc, char* argv[])
{
  long yield=0;
  for (int i=1; i < argc; i++) {
    msg("Reading: %s", argv[i]);
    SeqStream ss = SeqStream_open_single(argv[i]);
    Seq s;
    while (!Seq_read(&ss, &s)) {
      yield += s.len;
    }
  }
  printf("%ld\n", yield);
  return 0;
}

