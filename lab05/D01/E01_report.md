<!--
vim: tabstop=4 shiftwidth=4
-->
Fanti Andrea 235808

# Lab 05 exercise 01
The creation of a process in order to parallelize the 2 file sorting is useful
to speed up the elaboration (especialy when sorting very large files).

The created binary files are not portable since their internal structure
depend on how many bytes are used to represent an integer.

To delete the `.bin` files the `unlink()` POSIX function has been used.

It is interesting to notice that the generated random numbers are always the
same since the seed does not change.
