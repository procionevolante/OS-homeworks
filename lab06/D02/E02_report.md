<!--
vim: tabstop=4 shiftwidth=4
-->
Fanti Andrea 235808

# Lab 06 exercise 02
In order to not send unneded data over the pipe, before transmitting
the filename its length is sent as integer over the pipe.  
This introduces a problem since many children may be waiting to receive
the filename's length and could read the starting portion of the filename
as an integer.

In order to solve this problem a fouth pipe as been introduced.  
This pipe contains a "token" that a child process has to read before reading
the filename. After the filename has been correctly received the process
releases the token into the pipe with a `write`, unlocking another
process that was stuck at the `read` of this pipe, (called `lock`).

This program is not parallelized since only one child at a time is actually
sorting a file in the directory `dir`.

The execution could be parallelized by satisfying every request (until no file
has to be sorted anymore) on `request_pipe` before elaborating the responses
on `answer_pipe`.
