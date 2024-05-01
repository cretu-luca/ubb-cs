#!/bin/bash

if [ $# -eq 0 ]; then
	echo "no"
	exit 1
fi

for u in $0; do
	# if grep -E -q "^$u:" test_ps.txt; then 
	if id $u > /dev/null 2> /dev/null; then
		count=`ps -u $u | awk 'NR > 1' | wc -l`
		echo "$u - $count"
	fi
done
