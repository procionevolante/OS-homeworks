<!--
vim: tabstop=4 shiftwidth=4
-->
Fanti Andrea 235808

# Lab 09 exercise 03
The exercise 2 is tested by executing `e02` in background, redirecting its
output in a temporary file.

The pid of the background process can either be read on the shell variable `$!`
or captured from the output of the program `jobs -p`.

After the pid is known, signals are sent to the process by using the program
`kill -`_`signal PID`_.
Note that to ensure the signals are received in the same order, we wait one
second between one `kill` execution and the other.

The correctness of the program is checked by reading the temporary file and
counting the number of success and error messages.
