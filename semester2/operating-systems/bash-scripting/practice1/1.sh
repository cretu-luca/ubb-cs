#!/bin/bash

# user1 n1 user2 n2...
# check whether userx connected nx times

if [ `expr $# % 2` -eq 1 ]; then
	echo "odd number of arguments"
	exit 1
fi

echo "" >> sol.txt

while [ $# -gt 0 ]; do
	echo $1 $2
	if grep -E -q "^$1:" passwd.fake ; then
		if echo $2 | grep -E -q "^[1-9][0-9]*$"; then
			nr=`cat last.fake | grep -E "Fri[ ]*Apr" | grep -E -c "^$1"`
			if [ $nr -ge $2 ]; then
				echo $1 logged at least $2 times >> sol.txt
			else
				echo $2 logged less than $2 times >> sol.txt
			fi
		else
			echo $2 is not a number >> sol.txt
		fi
	else
		echo $1 is not a valid user >> sol.txt
	fi
	shift 2
done
