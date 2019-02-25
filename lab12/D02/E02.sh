#!/bin/bash
# Fanti Andrea 235808
# lab 12 exercise 02

if [ $# -ne 3 ]; then
	echo USAGE: $0 {dir} {function_name} {out_file}
	exit 1
fi

dir="$1"
func="$2"
if [ -z `echo "$out" | grep -E "^/"` ]; then
	out="$(pwd)/$3"
else
	out="$3"
fi
echo -n > "$out"

cd "$dir"
find . -type f -iname "*.c" -exec grep -nEH "$func[ \t]*\(" '{}' ';' > "${out}.tmp"

while read -r match; do
	echo elaborating "'$match'"
	filename=$(basename "$(echo "$match" | cut -d ':' -f 1)")
	linenum=`echo "$match" | cut -d ':' -f 2`
	line=`echo "$match" | cut -d ':' -f 3-`
	echo "${filename}, at line #${linenum}:$line" >> "$out"
done < "${out}.tmp"
rm "${out}.tmp"
