#!/bin/bash

files=`find $1 -type f -name "*.c"`
count=0

for file in $files; do

	if [ $count -gt 1 ]; then
		break
	fi

	lines=`cat $file | wc -l`	
	
	if [ $lines -gt 500 ]; then

		echo "$file"
		count=$((count+1))

	fi

done
