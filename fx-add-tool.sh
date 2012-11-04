#!/bin/sh

if [ $# -lt 1 ]; then
  echo "Create stub .c/.h files for a new tool"
  echo "Usage: $0 <toolname>"
  exit 1
fi

TOOL=$1
HFILE="fx-$TOOL.h"
CFILE="fx-$TOOL.c"

if [ -f $CFILE -o -f $HFILE ]; then
  echo "Tool '$TOOL' already exists. Remove $HFILE and/or $CFILE first."
  exit 1
fi

echo "Create new tool stubs $CFILE and $HFILE ?"
echo "(CTRL-C to quit)"
read

cat "fx-count.h" | sed "s/count/$TOOL/g" > $HFILE
echo "Wrote $HFILE"

cat "fx-count.c" | sed "s/count/$TOOL/g" > $CFILE
echo "Wrote $CFILE"


