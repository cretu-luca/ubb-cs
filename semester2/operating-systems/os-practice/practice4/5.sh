#!/bin/bash

# Write a bash script that receives as a parameter a number N and continuously
# reads strings from standard input. For each read string, if it is a regular file, 
# the script prints its name and number of lines and adds the number of lines to 
# a total. The script stops reading strings after the total number of lines from 
# files exceeds N and prints the first N lines from the concatenation of the read filenames

N=$1
shift 

total=0
string=""

while true; do
	
	if [ $total -gt $N ]; then
		echo done
		break
	fi

	read string

	if [ -f $string ]; then

		lines_c=`cat $string | wc -l`
		echo $string, $lines_c

		total=$((total+lines_c))
		lines=`echo "$lines" "$string"` 
	fi
	
	echo $total lines up until now

done

cat $lines | head -n $N
echo $total lines in total 
