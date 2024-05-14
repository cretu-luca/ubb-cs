#!/bin/bash

# 14. Write a bash script that receives a folder name as an argument. Find recursively in the folder
# the number of times each file name is repeated.

if [ ! -d $1 ]; then
	echo not a dir
	exit 1
fi

for file in `find $1`; do
	
	count=0

	for file2 in `find $1`; do
 		
		if [[ $file =~ $file2 ]]; then
			count=$((count+1))
		fi

	done

	echo $file appears $count times 

done
