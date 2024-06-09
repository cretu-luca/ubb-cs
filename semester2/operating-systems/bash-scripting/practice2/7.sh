#!/bin/bash

total_size=0

for file in $(ls $1); do
	
	file_size=$(du -b "$1/$file" | awk '{print $1}') 
	total_size=$((total_size + file_size))

done

echo $total_size
