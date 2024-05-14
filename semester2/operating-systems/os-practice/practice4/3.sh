#!/bin/bash

# Write a bash script that retrieves all the home folders of the exam and 
# practice accounts on the system and reports all such folders that have 
# any permissions set for group or for others as well as the student 
# username (not the account username) that those folders belong to.

seq=$1
shift

for arg in $@; do

	if [ -f $arg ]; then
		
		count=`cat $arg | grep -E -c "$seq"`
		if [ $count -gt 0 ]; then
			echo file $arg contains $seq
		fi

	elif [ -d $arg ]; then
		
		files=`find $arg`
		count=`echo $files | grep -E -c "$seq"`

		if [ $count -gt 0 ]; then
			echo dir $arg contains a file called $seq
		fi
	
	fi
	

done
