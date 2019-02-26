<!--
vim: tabstop=4 shiftwidth=4
-->
Fanti Andrea 235808

# Lab 05 exercise 02
The system call `execlp` accepts parameters through a null-terminated list.
`execlp` searches the `PATH` environment variable for the program file
to execute.

We can do this exercise using single child process *at a time*
(forking and sort a file, waiting for it to finish, then forking and
sorting the other one), but that would not provide any speed increase
over the use of 2 children processes.  
Doing this using only one child process and still executing `sort` is impossible
since the `exec` system call replaces the process image with a new one, making
restoration of the original execution flow impossible.
