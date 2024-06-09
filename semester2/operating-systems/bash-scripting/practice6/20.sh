#!/bin/bash

# Write a shell script that receives any number of words as command line arguments, and
# continuously reads from the keyboard one file name at a time. The program ends when all
# words received as parameters have been found at least once across the given files.

files=""

while true; do

	read filename
	if [ -f $filename ]; then
	
		files="$files $filename"

		echo $files
	
		count=0
		content=`cat $files`
		for word in $@; do

			found=`echo $content | grep -E -c "$word"`
			count=$((count+found))

			echo $word - $found
			
		done

	fi

	if [ $count -eq $# ]; then
	
		echo done
		exit 0

	fi
	
done
