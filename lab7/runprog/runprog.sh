#!/bin/sh

echo $*
#trap \'\' 1 2 3 15
ans=`exec $*`
#ans=" `execvp $*`"
echo $ans

echo end