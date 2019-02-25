#!/bin/awk -f
# Alternative solution using awk
{
	for (i=1; i < NF; i++){
		if (words[$i] == "")
			words[$i]=1
		stat[$i]++
	}
}
END{
	for (w in words)
		printf "'%s' -> %d\n", w, stat[w]
}
