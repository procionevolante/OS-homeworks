<!--
vim: tabstop=4 shiftwidth=4
-->
Fanti Andrea 235808

# Lab 07 exercise 03
This exercise is very similar to the second exercise of laboratory 3.
The exercise from lab 3 is easier to solve in the sense that memory duplication
is done automatically by the operating system, so we have "only" to populate
an array with the PID of each process before forking.

Here instead the memory address space is shared, so each thread would overwrite
previously written values on the array.

To solve this problem, and also to reduce memory usage, I decided to create
a tree in which each node is used by a single thread, but that maintains also
the pointer to the parent node.  
This structure allows one thread to find out which is its generation tree.

The main thread generates the root node that has `NULL` as the parent pointer
and performs the first call to the `populate` recursive-like function.
