#!/bin/bash

# 1. Write a bash script that counts all the C files from a given directory and all of its subdirectories.

# $1 - given directory

count=0

if [ ! -d $1 ]; then
	echo $1 must be a directory
	exit 1
fi

files=`find $1`

for file in $files; do
	count=$((count + 1))
	
	if [ -f $file ]; then 
		if grep -E -q ".c" $file; then
			echo $file is a file
		fi
	fi
	echo $count $file

done

echo $files
