#!/bin/bash

# 20. Write a shell script that receives any number of words as command line arguments, 
# and continuously reads from the keyboard one file name at a time. 
# The program ends when all words received as parameters have been found at least 
# once across the given files.

if [ $# -eq 0 ]; then
	echo "please provide at least one argument"
	exit 1
fi

found_all=false
all_files=""

while ! ${found_all}; do
	
	read -p "filename: " file
	if [ -z "$file" ]; then
		echo "please input a non empty string"
	elif [ ! -f "$file" ]; then
		echo "$file is not a file"
	else
		all_files="$all_files $file"
		found_all=true

		for word in $@; do

			if grep -E -q "\<$word\>" $all_files; then
				echo "found word $word"
			else
				found_all=false
			fi
		done
		fi
done

echo "all done"
