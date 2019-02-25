#!/bin/bash
# Fanti Andrea 235808
# lab 08 exercise 03
if [ $# -ne 2 ]; then
	echo USAGE: $0 in_file product
	exit 1
fi

echo
echo "$1" sorted by Product field:
head -n 1 "$1"
tail -n +2 "$1" | sort -rk 1

echo
echo "$1" sorted by Quantity field:
head -n 1 "$1"
tail -n +2 "$1" | sort -nk 2

echo
echo -n "$2 total quantity: "
#tot=`grep -iE "^$2[[:space:]][0-9]+\$" "$1" | cut -f 2 | paste -s -d + - | bc`
tot=0
for qty in `grep -iE "^$2[[:space:]][0-9]+\$" "$1" | cut -f 2`; do
	let tot+=$qty
done
echo $tot

echo list of products in capital letters:
cut -f 1 "$1" | sort | uniq | tr a-z A-Z
