#!/bin/bash
# Fanti Andrea 235808
# lab 09 exercise 03

#set -x

./e02 > output &
pid=$!
#pid=`jobs -p`
echo process started, pid=$pid

sleep 2

kill -SIGUSR1 $pid
sleep 1
kill -SIGUSR1 $pid
sleep 1
kill -SIGUSR2 $pid
sleep 1
kill -SIGUSR2 $pid
sleep 6
if [ `grep -i success output | wc -l` -eq 2 ]; then
	echo success messages printed
else
	echo success messages NOT printed
fi

kill -SIGUSR1 $pid
sleep 1
kill -SIGUSR2 $pid
sleep 1
kill -SIGUSR1 $pid
sleep 6
if [ `grep -i error output | wc -l` -eq 4 ]; then
	echo error messages printed
else
	echo error messages NOT printed
fi

kill -SIGUSR1 $pid
sleep 1
kill -SIGUSR1 $pid
sleep 6

if [ -z "`ps -o pid='' -g $pid`" ]; then
	echo program succeffully terminated
else
	echo program did NOT terminate, killing it now
	kill $pid
fi
rm output
