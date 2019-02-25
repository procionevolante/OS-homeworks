<!--
vim: tabstop=4 shiftwidth=4
-->
Fanti Andrea 235808

# Lab 09 exercise 02
The program works by maintaining an history of the last 3 signals received
(an array of 3 integers).

This array is updated inside the signal handler.  
After updating the `hist` array it is checked to search if one of the
conditions described in the exercise's text has been met, in which case an
appropriate counter is increased.

With this method we can manage multiple _success_ or _error_ messages if the
conditions are met multiple time during the 5 seconds of waiting time.

Once the `terminate` flag is set and the waiting time has passed, the program
stop its execution.
