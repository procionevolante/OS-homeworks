<!--
vim: tabstop=4 shiftwidth=4
-->
Fanti Andrea 235808

# Lab 08 exercise 01
One line is read at a time from the file by means of input redirection.

The input of the `read` command is read from the file specified as argument.
The cycle executes its core until the read execution fails (i.e., the
exit status of `read` is non-zero)

The line length can be calculated using the `wc -c` command or the bash
builtin function `${#var}`.  
While the first calculates the lenght in bytes of the string, the
second one also uses the locale to elaborate characters not in the ASCII table
to provide a more precise result.
