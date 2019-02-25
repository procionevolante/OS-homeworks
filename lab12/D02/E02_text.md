<!--
vim: tabstop=4 shiftwidth=4
-->
# Lab 12 exercise 02
Implement a `bash` script that takes three parameters on the command line,
the name of a directory, the name of a function, and the name of an output file.

The script must find within all the files in the subtree of the specified
directory all occurrences of the function, and save in the output file,
the filename, the line number, and the line in which the function appears.

The output file must be sorted according to the file name (primary key) and to
the line number (secondary key).
