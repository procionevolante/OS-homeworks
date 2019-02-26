<!--
vim: tabstop=4 shiftwidth=4
-->
Fanti Andrea 235808

# Lab 09 exercise 04
The script reads one line at a time from the log file and processes it.

For each line that meet the requirements the corresponding IP address is saved
into a temporary file.  
The date, request type and server answer are checked by means of a regular
expression.  
The username is checked using `grep` on the list of acceptable usernames,
to see if the user on the current line (retrieved using `cut -d ' ' -f 2`)
is among the parameters. Note that the list of users has been modified
to store one user per line so that if a username is a substring of another one
the condition isn't positive.

It is assumed that resources' name and usernames do not contain space
characters.

At the end, the file is printed using a `sort` command piped through `uniq`
to remove multiple occurrences.
