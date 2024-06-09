#!/bin/bash

# 3. Write a bash script that counts all the lines of code in the C files from the directory given as
# command-line argument and all its subdirectories, excluding lines that are empty or contain
# only spaces.

count=0

for arg in $@; do
	if [ -d $arg ]; then
		files=`find $arg | grep -E "\.c"`
		val=`cat $files | grep -E -c "[^\s]"`
		count=$((count+val))
	fi
done

echo $val
