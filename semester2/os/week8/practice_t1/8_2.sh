#!/bin/bash

while true; do

	read -p "Enter filename or stop: " file
	if [ "$file" == "stop" ]; then
		echo "Done"
		exit 0
	elif [ -f "$file" ]; then
		if file $file | grep -E -q "text"; then
			echo "File: $file - Words on first line: $(head -1 $file | wc -w)"
		fi
	fi

done
