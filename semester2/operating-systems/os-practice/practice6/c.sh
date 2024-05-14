#!/bin/bash

# delete appearance of word that is multiple of 3 from file

file=`cat $1`
word=$2

count=0

IFS=$'\n'
for line in "$file"; do

	echo "$line"

done
