<!--
vim: tabstop=4 shiftwidth=4
-->
# Lab 10 exercise 01
Implement a C program, `generation_tree_number.c`, which receives a command line
parameter: `n`. The parent process, pushes its ID number (__1__) in a vector,
creates two children and terminates.
Each child, pushes its number in its vector, creates another two children,
and terminates.

__Process creation stops after 2^n leave processes have been created.__
Each leaf child pushes its number in its vector, and print its generation tree, i.e., the sequence of its
saved IDs. Example:
```
> generation_tree_number 3
Process tree: 1 3 7 15
Process tree: 1 2 5 11
Process tree: 1 3 7 14
Process tree: 1 2 5 10
Process tree: 1 3 6 13
Process tree: 1 2 4 9
Process tree: 1 3 6 12
Process tree: 1 2 4 8
```
Hint:  
Draw the tree for n=3 and check that the number of the process at the second
level begins by 2, the number of the process at the third level begins by 4,
number of the process at the fourth level begins by 8 etc..)
