<!--
vim: tabstop=4 shiftwidth=4
-->
Fanti Andrea 235808

# Lab 12 exercise 03
The exercise is easily solved using a single succession of pipes:
1.	the file is read using `cat`
2.	all space characters are converted to newlines using `tr`
	(the `-s` flag removes adjacent repetitions of the first set of characters)
3.	the output is sorted
4.	repetitions are removed using `uniq`, the `-c` flag counts and print
	the number of successive equal lines
