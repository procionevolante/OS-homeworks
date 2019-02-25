<!--
vim: tabstop=4 shiftwidth=4
-->
# Lab 07 exercise 03
Implement a C program, `thread_generation_tree`, which receives a command line
parameter: `n`. It behaves exactly as the solution of Exercise 1,
but each leaf thread must print its generation tree, i.e., the sequence of
thread identifiers from the main thread.
Example:
```
> thread_generation_tree 3
Tread tree: 3077879488 3069483888 3052575600 3077876592
Tread tree: 3077879488 3069483888 3052575600 3035790192
Tread tree: 3077879488 3069483888 3060968304 3052575600
Tread tree: 3077879488 3069483888 3060968304 3027397488
Tread tree: 3077879488 3077876592 3044182896 3060968304
Tread tree: 3077879488 3077876592 3044182896 3019004784
Tread tree: 3077879488 3077876592 3069483888 3044182896
Tread tree: 3077879488 3077876592 3069483888 3010612080
```
