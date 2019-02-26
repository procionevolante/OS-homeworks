<!--
vim: tabstop=4 shiftwidth=4
-->
Fanti Andrea 235808

# Lab 08 exercise 04
To understand what type of file we are elaborating, we use the `test` command:
* with `test -d` we check if a file is a directory
* with `test -f` we check if a file is a regular file

In this script, `test` is actually called with its alias, `[`.  
The same program is used to check if the user has read and/or write access
to a file.

To count how many subdirectories a directory has, we count the number of lines
of `ls -l` that starts with the '`d`' character.

To ensure the files are processed in alphabetic order, the `ls` output is
piped through `sort`.
