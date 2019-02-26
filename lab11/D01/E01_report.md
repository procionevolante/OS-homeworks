<!--
vim: tabstop=4 shiftwidth=4
-->
Fanti Andrea 235808

# Lab 11 exercise 01
For each thread there is declared a function of the same name.

Each thread receives as parameter all the `sem_t` semaphores declared in the
main thread.

Threads B and C are unlocked by executing a `sem_post` 2 times on the `sems[0]`
semaphore.

Both B and C increase by 1 another semaphore that is decreased two times by D
before starting its execution.
