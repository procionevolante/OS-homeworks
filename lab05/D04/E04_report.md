<!--
vim: tabstop=4 shiftwidth=4
-->
Fanti Andrea 235808

# Lab 05 exercise 04
To ignore a signal we have to specify `SIG_IGN` as the signal handler in the
`signal()` call.

After telling the kernel we want the signal to be ignored, there is no way to
know when 5 of these signals have arrived.

The child process therefore sends a `SIGUSR2` signal to reactivate `SIGUSR1s`
reception and then sends the last `SIGUSR1` before terminating execution.
