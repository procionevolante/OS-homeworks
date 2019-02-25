<!--
vim: tabstop=4 shiftwidth=4
-->
Fanti Andrea 235808

# Lab 04 exercise 01
To wait for the child process to finish in this program it is sufficient to use
the `wait()` system call because we don’t need to differentiate between children
(we have only one).

The PIDs change between runs because they are assigned by the operating system
from the ones available.  
They are the same inside the same run because the parent process waits for the
child before exiting.  
If the parent wouldn’t do this (and it sleeps for less than its child), the
child process would be inherited by the init process (with PID equal to 1).
