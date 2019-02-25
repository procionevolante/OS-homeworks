#!/bin/sh
# Fanti Andrea 235808
# lab 08 exercise 04
if [ $# -ne 2 ]; then
	echo USAGE: $0 [dir] [out]
	exit 1
fi

dir=$1
if [ `echo "$2" | grep -e "^/" | wc -l` -eq 1 ]; then
	out=$2
else
	out=`pwd`/$2
fi

if [ ! -d "$dir" ]; then
	echo ERROR: \'$dir\' is NOT a directory
	exit 1
fi

# delete file $out if it already exists
[ -f "$out" ] && rm "$out"

cd "$dir"
for f in `ls | sort`; do
	if [ -f "$f" ]; then
		echo ---FILE $f--- >> "$out"
		pwd >> "$out"
		echo dimension: `ls -l "$f" | tr -s ' ' | cut -d ' ' -f 5` bytes >> "$out"
		echo -n "user has read permission: " >> "$out"
		if [ -r "$f" ]; then
			echo Y >> "$out"
		else
			echo N >> "$out"
		fi
		echo -n "user has write permission: " >> "$out"
		if [ -w "$f" ]; then
			echo Y >> "$out"
		else
			echo N >> "$out"
		fi
	elif [ -d "$f" ]; then
		echo ---DIR $f--- >> "$out"
		pwd >> "$out"
		echo `ls -l "$f" | grep -E '^d' | wc -l` subdirectories >> "$out"
	fi
done
