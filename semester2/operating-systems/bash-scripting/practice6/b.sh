#!/bin/bash

# read strings until stop is read
# count how many start with vowel

count=0

while true; do

	read string
	if [[ $string =~ "stop" ]]; then

		echo done
		break

	fi

	vowel=`echo $string | grep "^[aeiouAEIOU]" | wc -l`

	if [ $vowel -eq 1 ]; then
	
		echo $string starts with vowel
		count=`expr $count + 1`

	else

		echo $string does not start with vowel

	fi
done

echo $count started with vowel
