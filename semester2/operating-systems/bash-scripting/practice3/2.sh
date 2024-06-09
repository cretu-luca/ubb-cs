#!/bin/bash

# Find recursively in a directory all ".c" files having more than 500 lines. Stop after finding 2 such files.

count=0

for file in `find $1`; do
	
	if [ $count -gt 1 ]; then
		break
	fi

	if [ -f $file ]; then 
		if [ `echo "$file" | grep -E -c "\.c$"` -gt 0 ]; then

			lines=`cat $file | grep -c -v "^$"`

			if [ $lines -gt 500 ]; then
				count=$((count+1))
				echo $file
			fi
		fi	
	fi

done
