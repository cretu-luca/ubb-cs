#!/bin/bash

# 6. Write a bash script that sorts the file given as command line arguments in ascending order according to their file size in bytes.

if [ $# -eq 0 ]; then
	echo no arg
	exit 1
fi

for arg in $@; do
	
	file_size=`du $arg | awk "{print $1}"`

	echo $file_size

done
