#!/bin/bash

if [ -z "$1" ]; then
	echo "no parameters given"
	exit 1
fi

if [ ! -d "$1" ]; then
	echo "parameter is not a folder" 
	exit 1
fi

total=0
for f in $(find $1 -type f | grep -E "\.c"); do
	nr_lines=$(grep -E -c -v "^[ \t]*$" $f)
	echo "$f - $nr_lines"
	total=$((total+nr_lines))

done

echo "total lines: $total"
