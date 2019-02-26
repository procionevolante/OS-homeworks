<!--
vim: tabstop=4 shiftwidth=4
-->
# Lab 05 exercise 04
Write a C program that generate a child. The parent opens a file given as an argument of the command
line, then loops forever, 1) reading each line, 2) printing the line number and the line content 3)
rewinding the file. The child process sends a `SIGUSR1` signal to the parent at random intervals
between `1` and `10` seconds. The first received signal makes the parent skip the print statement. It will
restart printing after receiving the next `SIGUSR1` signal. This behavior is repeated for all the received
`SIGUSR1` signals. After a random number of times `[10-20]` a `SIGUSR1` signal has been received,
the next `5 SIGUSR1` signals must be ignored. Finally, and after receiving another `SIGUSR1` signal
both parent and child must terminate.

Before its termination, the parent must print the number of `SIGUSR1` signals that have been sent.
