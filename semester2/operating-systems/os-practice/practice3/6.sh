#!/bin/bash

files=`find $1 -type f`

for file in $files; do

	
	if [ -w $file ]; then
	
		perm=`ls -l $file | awk '{print $1}'`
		echo $perm $file
		
		chmod -w $file

		perm=`ls -l $file | awk '{print $1}'`
		echo $perm $file

		chmod +w $file

	fi	
done
