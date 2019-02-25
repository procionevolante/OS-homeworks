#!/bin/bash
# Fanti Andrea 235808
# lab 08 exercise 02
until [ -z "$1" ]; do
	echo -n "processing file $1 ... "
	while read -r line ; do
		let i=0
		tmp=''
		for w in $line ; do
			if [ $i -eq 2 ]; then
				tmp="$tmp $(echo -n $w | tr a-z A-Z)"
			else
				tmp="$tmp $(echo -n $w)"
			fi
			let i++
		done
		# we take only from the second character to remove the first " "
		echo "$tmp" | cut -c 2- >> "$1~"
	done < "$1"
	mv "$1~" "$1"
	echo done
	shift 1
done
