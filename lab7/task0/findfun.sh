#!/bin/sh

b=" `find -type f -name "*.c"` "

b=" `grep -l "$1()" $b` "

#b='a.c b.c c.c'

for x in $b
  do
    echo $x
    echo =============================================
    grep -A 5 $1 $x
    echo =============================================
  done

exit 0