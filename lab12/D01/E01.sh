#!/bin/bash
# Fanti Andrea 235808
# lab 12 exercise 01

dir=$1
if [ -z "$dir" ]; then
	echo -n "insert a directory: "
	read dir
fi

cd "$dir"

for file in *.txt; do
	if [ -f "$file" ]; then
		mv "$file" "$(echo "$file" | tr A-Z a-z)"
	fi
done
