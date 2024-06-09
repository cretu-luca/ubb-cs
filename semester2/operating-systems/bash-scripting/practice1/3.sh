#!/bin/bash

if [ `expr $# % 2` -eq 2 ]; then
	echo "number of arguments must be even"
	exit 1
fi

echo "" > sol2.txt

countzero=0

while [ $# -gt 0 ]; do
	dir=$1
	file=$2
	if [ ! -d $dir ]; then
		echo "$dir - not a directory!"
		exit 1
	fi

	if [ ! -f $file ]; then
		echo "$file - not a file!"
		exit 1
	fi
	shift 2
	
	count=`find $dir | grep -E -c "$file$"`

	if [ $count -eq 0 ]; then
		countzero=`expr $countzero + 1`
	fi

	echo "$dir $file $count" >> sol2.txt
done

sort -n -k3 sol2.txt

