#!/bin/bash

# Write a bash script that takes any number of usernames as command line
# arguments. You must validate that the provided arguments are existing 
# usernames. The script will print the total number of processes per 
# valid user once a second. If no arguments are given, the script 
# should print a message and then terminate.

if [ -z $1 ]; then
	echo bye!
fi

for arg in $@; do

	count=`grep -E -c "^$arg" ps.fake`

	if [ $count -ne 0 ]; then
		echo $arg - $count
	else 
		echo $arg is an invalid username

	fi
	
done
