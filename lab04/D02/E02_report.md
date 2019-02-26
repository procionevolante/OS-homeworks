Fanti Andrea 235808

# Lab 04 exercise 02
We can use `ps -la` to see a list of all processes (that comprises the various
parent-child).  
To kill a process, we can execute `kill -9 {process PID}`.

We notice that when a child process terminates before its parent, it goes into a
`Z` status (Z stands for zombie): it means that it is waiting for its exit
status to be captured by the parent.
