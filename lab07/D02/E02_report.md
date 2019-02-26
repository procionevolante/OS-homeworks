<!--
vim: tabstop=4 shiftwidth=4
-->
Fanti Andrea 235808

# Lab 07 exercise 02
This program functions in a way very similar to the execution of a recursive
function, as each thread creates another two threads and waits for them
to exit.

The first call to the function `print_recursive` is done "normally"
directly from the main function.

Each thread receives as parameter the number of tree's levels still
to be created.  
When this number reaches 0, the creation stops and the thread
identifier (retrieved with `pthread_self`) is printed.
