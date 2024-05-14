#!/bin/bash

# Write a script that receives as command line arguments pairs consisting of a filename and a
# word. For each pair, check if the given word appears at least 3 times in the file and print a
# corresponding message.

if [ `expr $# % 2` -ne 0 ]; then

	echo $invalid number of arguments
	exit 1

fi

while true; do

	if [ -z $1 ]; then

		echo done, bye
		exit 0

	fi

	filename=$1
	word=$2
	shift 2

	if [ -f $filename ]; then
		
		count=`cat $filename | grep -o "\<$word\>" | wc -l`

		if [ $count -ge 3 ]; then

			echo $word apprears $count times in $filename
	
		else

			echo $word appears only $count times in $filename

		fi
	
	else
		
		echo file $filename does not exist

	fi

done
