<!--
vim: tabstop=4 shiftwidth=4
-->
Fanti Andrea 235808

# Lab 10 exercise 01
The new IDs starting from the ID of the current process (referred to
`myid`) are `myid*2` and `(myid*2)+1`.

In this way, each process has its own unique ID.

To store the IDs, it is sufficient to use an array that is populated inside
the `for` loop, since the `fork()` duplicates the process' memory, that
comprises the `ids` array.
