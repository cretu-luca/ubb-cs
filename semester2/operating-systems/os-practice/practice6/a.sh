#!/bin/bash

# user1 n1 user2 n2...
# check whether userx connected nx times

if [ `expr $# % 2` -eq 1 ]; then
	
	echo invalid number of arguments
	exit 1

fi

while true; do

	if [  $# -eq 0 ]; then

		echo done
		exit 0

	fi
	
	user=$1
	N=$2
	shift 2

	count=`cat "last.fake" | grep "^$user" | wc -l`

	if [ $count -gt $N ]; then
	
		echo $user connected $count times, which is more than $N

	else

		echo $user connected $count times, which is less than $N

	fi

done
