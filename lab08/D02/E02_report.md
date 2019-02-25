<!--
vim: tabstop=4 shiftwidth=4
-->
Fanti Andrea 235808

# Lab 08 exercise 02
To simplify the solution, in this exercise I assumed that each word
is separated only by a single space character from all the others.

Once the line is read from the file (as in the first exercise), the words
are extracted from the line using a `for` loop.  
The third word is converted using a `tr` command.

The elaboration of the argument list is done using a `shift 1` command
and a loop.  
Basically, inside the loop the elaborated file is always `$1`, but the
argument list is shifted by one position down at each iteration.  
The elaboration stops once `$1` has zero length (i.e., there are no more
arguments).

For each input file, a temporary file is created while the conversion is
in progress. At the end, this file replaces the original one.
