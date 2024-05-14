#!/bin/bash

# delete appearances of word that is a multiple of 3 from file

file=`cat $1`
word=$2

count=0

while read line; do

	for word2 in $line; do
		
		if [[ $word2 =~ $word ]]; then
			
			count=`expr $count + 1`
			

			if [ `expr $count % 3` -ne 0 ]; then
	
				echo $word2

			fi
		else
		 	echo $word2
		
		fi


	done

done < $1
