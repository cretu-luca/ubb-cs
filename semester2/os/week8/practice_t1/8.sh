#!/bin/bash

# 8. Write a script that reads filenames until the word "stop" is entered.
# For each filename, check if it is a text file and if it is, 
# print the number of words on the first line.(Hint: test command to
# check if regular file; file command to check if text file)

cuv=""

while read cuv; do
	if [ ! "$cuv" == "stop" ]; then
	
		if [ -f $cuv ]; then

			cat $cuv | head -n1 | awk "{print NF}"

		fi

	else
		echo final
		break
	fi
done
