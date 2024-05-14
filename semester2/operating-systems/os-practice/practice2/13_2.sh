#!/bin/bash

for link in $(find "$1" -type l); do
	if [ ! -e "$link" ]; then
		echo "Link $link is not valid"
	fi
done
