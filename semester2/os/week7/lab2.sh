#!/bin/bash

first_arg=$1

shift

for A in $@; do
	if test -f $A; then
		if grep -q $first_arg $A ; then
			echo $A "contains" $first_arg
		fi
	elif test -d $A; then
		# echo `ls $A`
		if find . -name $A; then
			echo "in " $A " there is a file called " $first_arg
		fi
	fi

done 
