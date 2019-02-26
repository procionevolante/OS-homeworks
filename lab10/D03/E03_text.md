<!--
vim: tabstop=4 shiftwidth=4
-->
# Lab 10 exercise 03
Implement a C program that simulates two clients that perform concurrent
bank transactions on accounts **1** and **2**.

The main thread creates two threads, which are owners of both accounts.
Initially the total money in the two accounts is 100000 Euro.

Thread `i` loops sleeping for a random interval (**0-8**) of seconds,
then it reads its current balance in account i, and after a random interval
(**0-4**) of seconds, it decides to move a random amount of money m,
(**1000-5000**) Euro, from account `i` to account `3-i`.

Of course, the transaction implies that the balance of account `i`
decreases by `m`, and the balance of account `3-i` increases by `m`,
the read and write operations on the same account must be performed in
mutual exclusion.

**Write a single code for the two threads.**

Analyze your solution, and comment the possibility of deadlock.
