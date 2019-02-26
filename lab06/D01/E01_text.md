<!--
vim: tabstop=4 shiftwidth=4
-->
# Lab 06 exercise 01
Write a C program in which a parent process creates two processes,
a producer and a consumer.

The producer reads lines of text from `stdin` and writes them to a pipe.

The consumer process reads data from the pipe and writes them to `stdout`,
converting text lines to capital letters.

Introducing the "__end__" string terminates both the child processes
and the parent process.
