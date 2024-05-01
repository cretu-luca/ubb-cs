#!/bin/bash

# write a bash script that receives as command line arguments file names
# the script will output the unique lines obtained by removing all letters  
# and digits from the files contents

if [ $# -eq 0 ]; then
	
	echo no arguments
	exit 1
	
fi

for arg in $@; do

	if [ -f $arg ]; then
		
		sed -E "s/[a-zA-z0-9]//g" $arg

	else
		echo not a valid filename
	fi


done | sort | uniq
