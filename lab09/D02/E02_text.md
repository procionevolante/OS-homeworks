<!--
vim: tabstop=4 shiftwidth=4
-->
# Lab 09 exercise 02
Write a __program__ that is able to handle signals `SIGUSR1`, `SIGUSR2`
and `SIGALRM` as follows:  
Every 5 seconds it controls the sequence of signals received, and
*	outputs an __error__ message if it received signals `SIGUSR1` followed by
	signal `SIGUSR2` or vice versa,
*	outputs a __success__ message if __two__ successive `SIGUSR1` (or `SIGUSR2`)
	signals,
*	terminates if it has received at least __three__ successive `SIGUSR1`
	(or `SIGUSR2`) signals.
