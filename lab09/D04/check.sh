#!/bin/bash
# Fanti Andrea 235808
# lab 09 exercise 04
if [ $# -lt 3 ]; then
	echo USAGE: $0 log_file date username...
	exit 1
fi
logfile=$1
date=$2
shift 2
users=`echo -n $* | tr ' ' '\n' | sort | uniq`

# check if temporary file already exists
if [ -f .tmp ]; then
	echo ERROR: temporary file \".tmp\" already exists >&2
	exit 5
fi

touch .tmp
while read -r line; do
	# check date, request type, server answer
	# check if the user is in the list
	if [ -n "$(echo "$line" | grep -E "\[$date[0-9:]{9}\] POST [[:alnum:][:punct:]]+ 200\$")" -a \
		-n "$(echo "$users" | grep -E "^$(echo "$line" | cut -d ' ' -f 2)\$")" ]
	then
		echo $(echo "$line" | cut -d ' ' -f 1) >> .tmp
	fi
done < "$logfile"

# printing final result
sort .tmp | uniq
# removing temporary file
rm .tmp
