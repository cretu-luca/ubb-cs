#!/bin/bash

# 3. Find recursively in a given directory all the symbolic links, and report those that point to
# files/directories that no longer exist. Use option -L to test if a path is a symbolic link, and option
# -e to test if it exists (will return false if the target to which the link points does not exist) 

if [ ! -d $1 ]; then # [ text ] -> test 
	echo not a dir
	exit 1
fi

# files=`find $1`



for file in `find $1`; do
	
	echo $file

	if [ -L $file ]; then
		echo $file
		if [ -e "$file" ]; then
			echo "$file - false"
		fi
	fi

done
