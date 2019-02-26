<!--
vim: tabstop=4 shiftwidth=4
-->
# Lab 04 exercise 01
Make a program `parent-child` that forks a single child process, then it
generates and __prints__ a random number `n1`, in range `[0-10]`, sleeps for
`n1` seconds, waits for its child to exit, retrieves the child's exit code,
and __prints__ it.

The child __prints__ his PID, the parent PID, and sleeps for `n2` seconds,
where `n2` is a random number in  range [0-10], then it generates a random
number `r` in range [0-255], and use it as its return code, then __prints r__ 
and its parent PID, and exits.

Run your program several times, and compare the parent PID printed by the child
before sleeping, and the one printed after sleeping. Are they always the same?
If not why?
