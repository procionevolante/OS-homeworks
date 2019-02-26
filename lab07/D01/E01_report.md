<!--
vim: tabstop=4 shiftwidth=4
-->
Fanti Andrea 235808

# Lab 07 exercise 01
The new thread is created with the `pthread_create` function.

The exit code is captured using the `pthread_join` function, that also waits for
the termination of a specific thread.

It is interesting to notice that the exit code of the thread cannot be
simply the address of one of its local variables, as their memory space
is repurposed once the thread exits.  
Instead, one should use a manually allocated variable, the address of one
of the main thread local variables (passed as argument), or the address of a
global variable.
