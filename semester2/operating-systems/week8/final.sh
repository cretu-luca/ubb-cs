#!/bin/bash

for arg in $@; do
	
	if [ -d $arg ]; then
	
		echo $arg is a dir
		textfiles=`find $arg`
		echo "$textfiles" | grep "\.txt"

	elif [ -f $arg ]; then
	
		is_sh=`echo $arg | grep "\.sh" | wc -l`

		if [ $is_sh -eq 1 ]; then
			
			echo $arg is a .sh file
			
			grep -E -v "^[ 	]*$" $arg

		fi

	fi

	echo -e '\n'

done
