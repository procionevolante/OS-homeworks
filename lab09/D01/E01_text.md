<!--
vim: tabstop=4 shiftwidth=4
-->
# Lab 09 exercise 01
Given a text file, passed as an argument of the command line
Implement a concurrent program using three threads (T1, T2, T3) that process
the file content in pipeline  
T1: Read from file the next character  
T2: Transforms the character read by T1 in uppercase  
T3: Displays the character produced by T2  
Upgrade the solution given in the thread slides, and the corresponding
C program, to process correctly the first two characters of the file, and files
with less than two characters.
