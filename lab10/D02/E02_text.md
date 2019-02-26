<!--
vim: tabstop=4 shiftwidth=4
-->
# Lab 10 exercise 02
Implement a C program, `generation_threads_tree_number.c`, which behaves
similarly to `generation_tree_number.c`, but prints the sequence of
thread numbers.

Please notice that we assume that we cannot pass variables in
`pthread_create()`.

Thus, each thread gets its ID number from a global variable
initialized to __1__.
