<!--
vim: tabstop=4 shiftwidth=4
-->
# Lab 12 exercise 04
A `bash` script receives two parameters, the name of a process, and a time
interval, `T`.

It must check every T seconds if the indicated process is still present in the
system.

If the process is found in the zombie state for more than 5 times the script
must terminate the process.

Tip: command `ps -el` provides an output similar to the following:

```
UID	PID	PPID	F		CPU	PRI	NI	RSS		S	ADDR	TTY	TIME		CMD
0	1	0		4000	0	31	0	568		Ss	6fd9cd4	??	0: 00.20	/sbin/launchd
0	10	1		4000	0	31	0	1292	R+	6fd9384	??	0: 00.59	/usr/libexec/kextd
0	11	1		4000	0	31	0	3412	Z	6fd982c	??	0: 02.10	/bin/ls
```
Properly parsed, it provides the necessary information to solve the problem.
Note that character `Z` in column `S` indicates that the process is in a
zombie state.
