#!/bin/bash

while test $# -gt 1; do
	echo "file $1 - int: $2"

	if [ -f $1 ]; then

	else
		echo "Argument $1 is not a file"
	fi
	shift 2
done
