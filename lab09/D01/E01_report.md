<!--
vim: tabstop=4 shiftwidth=4
-->
Fanti Andrea 235808

# Lab 09 exercise 01
The exercise has been changed using integers in place of characters as
argument for threads.

In this way, only when the argument is actually a character is elaborated
and printed.

The only thing done by the main thread (between thread synchronization) is to
shift the arguments so that the read character goes to the updating thread,
whose one in turn goes to the printing thread.

Once the reading thread fetch, using the `fgetc` function, `EOF`, the execution
is not interrupted but instead continues as normal, until the character of the
outputting thread is `EOF`.  
This gives time for the last 2 characters of the file to be updated and printed.

The first 2 printed characters are no more `' '`: this was "fixed" by setting
the initial value of the arguments to `'\0'`. Characters are elaborated only
if they are neither `\0` nor `EOF`.
