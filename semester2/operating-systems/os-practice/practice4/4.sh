#!/bin/bash

# Write a bash script that receives as command line arguments any number of
# triplets like D, N, M where D - folder name, N, M - integers. The script 
# will print the folder names that contain at least N and at most M regular 
# files (recursively). The script will check if the given folders exist. 
# The script will check if N < M and will print a message otherwise.

if [ `expr $# % 3` -ne 0  ]; then
	echo incorrect number of arguments
	exit 1
fi

while true; do

	if [ -z $1 ]; then
		echo done
		exit 1
	fi

	if [ ! -d $D ]; then
		echo director does not exist
	fi

	D=$1
	N=$2
	M=$3
	shift 3

	if [ `expr $N - $M` -gt 0 ]; then
		echo $N - $M is a wrong interval
	fi

	files_num=`find $D -type d | wc -l`
	
	if [ $files_num -gt $N ] && [ $files_num -lt $M ]; then
		echo $D
	fi

done
