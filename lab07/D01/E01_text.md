<!--
vim: tabstop=4 shiftwidth=4
-->
# Lab 07 exercise 01
Implement a C program that creates another thread `T`.
1.	Thread `T` has to display its thread identifier, its PID, and sleep for `n`
	seconds (`n` is passed as command line parameter)
2.	Before thread `T` exits, it asks the user to digit a number
	that will be used as its return code.
3.	The main thread waits thread `T` termination. It retrieves and displays
	the thread exit code.
	The main thread must also prints thread `T` identifier, and terminate.
