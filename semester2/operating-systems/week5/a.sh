#!/bin/bash

if [ -z "$1" ]; then
	echo "No file!"
	exit 1
fi

F=$1
Count=0

for [ $Count -lt 100 ]; do
	X=$(cat $F)
	X=$((X+1))
	echo $X > $F
	Count=$((Count + 1))
done
