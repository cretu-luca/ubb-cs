#!/bin/bash

files=`find $1 -type f -name "*.c"`
count=0

echo NO QUOTES
echo -- allows iterating over each file at once in for -- 

for file in $files; do
	
	count=$((count+1))
	
	echo file $count
	echo $file

done
