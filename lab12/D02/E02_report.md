<!--
vim: tabstop=4 shiftwidth=4
-->
Fanti Andrea 235808

# Lab 12 exercise 02
All the information needed can be gathered from the `grep -nEH` command.

To execute this command on every file in the directory specified a
`find` command with the `-exec` option is used.

A regular expression is used to search for the function. This is made
to match a function name followed by any number of space characters and the
"`(`" character.
