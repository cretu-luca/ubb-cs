#!/bin/bash

# 4. Write a bash script that receives any number of command line arguments and prints on the screen, for each argument, if it is a file, a directory, a number or something else.

for arg in $@; do
	if [ -f $arg ]; then
		echo $arg is a file
	else 
		if [ -d $arg ]; then
			echo $arg is a directory
		elif echo $arg | grep -E -q "^[0-9]+$"; then
			echo $arg is a number
		else 
			echo $arg is something else
		fi
	fi
done
