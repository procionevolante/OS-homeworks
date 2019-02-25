<!--
	vim: tabstop=4 shiftwidth=4
-->
Fanti Andrea 235808

# Lab 04 exercise 03
Since the created processes sleeps for a decreasing amount of time,
usually they become zombies before their PCB is collected by the parent,
who is waiting for the first process to exit.

When the parent process finishes waiting for the first child to exit, all
the other processes are already dead, so their PCBs is collected in bulk
without having to wait more time.

This behaviour is almost always as said previously, but it is entirely dependent
on the scheduler.
