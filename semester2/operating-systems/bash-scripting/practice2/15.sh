#!/bin/bash

file=`cat ps.fake`
users=""

for process in "$file"; do
	
	avg=0
	count=0
	user=$(echo "$process" | awk '{print $1}')

	for process2 in "$file"; do
	
		user2=$(echo "$process2" | awk '{print $1}')

		echo "$user2"

		if [[ "$user" == "$user2" ]]; then
			pid=$(echo "$process2" | awk '{print $2}')
			avg=$((avg+pid))
			count=$((count+1))
		fi
		
	done

	avg=$((avg / count))
	echo "$user" - $avg

done | sort | uniq



