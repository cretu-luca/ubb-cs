#!/bin/bash

files=`find $1 -type f -name "*log"`

for file in $files; do

	echo $file

	content=`cat $file | sort`
	echo "$content" > myfile.txt
	content=`cat myfile.txt`
	echo "$content" > $file

done
