<!--
vim: tabstop=4 shiftwidth=4
-->
Fanti Andrea 235808

# Lab 10 exercise 03
Each of the two threads manage a single bank account.

For each bank account it is specified:
* the owner thread
* the current balance
* a semaphore to lock the balance value management

Each thread reads its balance. To ensure the balance is not going to change
while its value is managed the corresponding mutex is locked.

After retrieving the balance, the thread sleeps for a random amount of time
before locking the other mutex and performing the transaction (and unlocking
all the mutexes).

There is a possibility of deadlock because a thread may try to lock the other
one's mutex after the other thread locked its own mutex to read the balance.  
In this scenario, each thread is waiting for the other one to perform the
transaction.
