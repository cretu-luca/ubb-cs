#!/bin/bash

# Write a script that finds in a given directory hierarchy, all duplicate 
# files and displays their paths. Hint: use checksums to detect whether two 
# files are identical.

initial_files=`find $1 -type f`
files=`find $1 -type f`
echo "" > myfile2.txt

for file in $files; do

	checksum=`md5sum $file` 
	echo $checksum

done > myfile2.txt

files=`cat myfile2.txt`

for file in $files; do

	checksum2=`echo $file | awk '!/^\./ {print $0}'`
	
	if [ ! -z $checksum2 ]; then 
	
		count=`grep -E -c "$checksum2" $files`

 		echo "$count"

	fi

done
