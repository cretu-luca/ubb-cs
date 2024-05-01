#!/bin/bash

# solving ex 3

# if [ $# -eq 0 ] 
if test $# -eq 0; then
	echo "no"
fi

# no spacing when assigning variables 

S=$1

shift

for f in $@; do
	if [ -f $f ]; then
		if grep -E -q "$S" $f; then
			echo "file yadayada"
		else
			echo "file does not contain" $S
		fi
	elif [ -d $f ]; then
		if [ 0 -lt $(find $f -name $S | wc - l) ]; then
			echo "dir $f contains file $S"
		fi
	fi

done
