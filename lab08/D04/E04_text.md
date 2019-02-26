<!--
vim: tabstop=4 shiftwidth=4
-->
# Lab 08 exercise 04
Write a shell script that receives as arguments in the command line two
arguments `dir` and `out`.  
It must check that `dir` is a directory, otherwise it displays an error
message and exits.  
If `dir` is a directory, it must check all files of the filesystem tree
rooted in that directory, and print the following information:

1.	If the file is a regular file, prints its pathname, its dimension, and
	if the user has read and write permissions
2. If the file is a directory, prints its pathname, and how many
	sub-directories it contains

Notice that the output of command `ls -l` is similar to this one:
```
drwx------	12 user user 408 Oct 30 19:09 Desktop
-rw-r--r--	 1 user user 192 Jul 13 00:03 pip
-rwxr-xr-x	 1 user user  74 Nov  3 10:02 fff.c
drwxrwxrwx	22 user user 408 Oct 30 12:09 tmp
```

The results must be saved in file `out`, sorted in alphabetic order.
