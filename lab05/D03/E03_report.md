<!--
vim: tabstop=4 shiftwidth=4
-->
Fanti Andrea 235808

# Lab 05 exercise 03
The `execv` system call does not provide automatic program file search, so the
file path had to be specified ("`/bin/sort`" in this case).

Note that this version of the program does not work when the `sort` program is
not in the `/bin` directory, even if the `PATH` environment variable has been
correctly set.
