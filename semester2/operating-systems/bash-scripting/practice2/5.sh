#!/bin/bash

# 5. Write a bash script that keeps reading strings from the keyboard until the name of a readable regular file is given.

while true; do
	read word
	
	if [ ! -f $word ]; then
		echo try again
	else
		echo fine!
		break
	fi

done
