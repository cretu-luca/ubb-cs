#!/bin/bash

if [ ! -f $1 ]; then
	echo $1 must be a file
	exit 1
fi

fisier=$1
shift

for litera in $@; do
	if [[ $litera =~ ^[a-z]$ ]]; then
		grep -E -i -o "\<$litera[a-z]*\>" $fisier > "${litera}.txt"
	else
		echo $litera nu este o litera
	fi
done
