<!--
vim: tabstop=4 shiftwidth=4
-->
Fanti Andrea 235808

# Lab 06 exercise 01
The `pipe` system call writes 2 file descriptors into the array passed by
argument that can be used to communicate between processes.  
In position 1 there is the file descriptor to write into the pipe and
in position 0 to read from it.

Since both the producer and the consumer knows what has been inserted,
they terminate when the string `end` is inserted.

The main process waits for the 2 children by means of two `wait(NULL)`
instructions, as we don't need neither to differentiate between processes
nor to catch their exit code.
