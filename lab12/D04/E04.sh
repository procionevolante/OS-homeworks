#!/bin/bash
# Fanti Andrea 235808
# lab 12 exercise 04

if [ $# -ne 2 ]; then
	echo USAGE: $0 {process_name} {time_interval}
	exit 1
fi

proc=$1
t=$2

# configure accordingly
stat_col=2
pid_col=4
cmd_col=14-

zombie_n=0
while true; do
	status=$(ps -el | tail -n +2 | tr -s ' ' | cut -d ' ' -f ${stat_col},${pid_col},${cmd_col} | grep "$proc")
	# process not present anymore, exiting
	[ -z "$status" ] && break
	if [ -n "$(echo "$status" | grep -E "^Z ")" ]; then
		let zombie_n++
		[ $zombie_n -eq 5 ] && kill $(echo "$status" | cut -d ' ' -f 2)
	else
		zombie_n=0
	fi
	sleep $t
done
