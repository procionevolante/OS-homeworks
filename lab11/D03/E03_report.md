<!--
vim: tabstop=4 shiftwidth=4
-->
Fanti Andrea 235808

# Lab 11 exercise 03
In this exercise the synchronization point is realized by means of 2
semaphores: both B and C increase just _one_ of these semaphores by 2, then,
D and E decrease _both_ of the semaphores by one.

Each thread receives as parameter, among the semaphore array `sems`, the
number of cycles `num_cycles`.

The cycle itself is implemented just as in exercise 2: thread A locks a
semaphore that is unlocked by thread F.
