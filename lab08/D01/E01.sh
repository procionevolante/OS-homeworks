#!/bin/bash
# Fanti Andrea 235808
# lab 08 exercise 01
if [ $# -ne 1 ]; then
	echo USAGE: $0 [file] >&2
	exit 1
fi
if [ ! -r "$1" ]; then
	echo ERROR: could not read $1 >&2
	exit 2
fi

echo longest line length:
maxlen=0
linenum=0
while IFS='' read -r line; do
	let linenum++
	#len=`echo -n "$line" | wc -c`
	len=${#line}
	[ $len -gt $maxlen ] && maxlen=$len
done < "$1"
echo $maxlen

echo total number of lines:
echo $linenum
