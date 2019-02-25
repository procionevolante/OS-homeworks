# Lab 04 exercise 03
Write a concurrent C program that reads from command line an argument `n`,
dynamically allocate an array `v` of size `n`, and read `n` values from `stdin`
and store the values in the array.
The main process creates `n` processes.
The first created child sleeps `n` seconds, the second child sleeps `n-1`
seconds, and so on so forth (last created child sleeps `1` second).
Each child after sleeping terminates returning as its status code the number
of seconds it has slept.
The parent must wait for its children sequentially **from the first created
to the last one**, printing their return code and the value of `v[i]`, where
`i` is the identifier of the process (0 to n-1).
