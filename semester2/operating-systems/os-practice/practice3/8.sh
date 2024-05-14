#!/bin/bash

# Display all the mounted file systems who are either smaller than 1GB 
# or have less than 20% free space.

df_info=`df`

IFS=$'\n'

for info in $df_info; do

	echo $info | awk '$2 > 1000000 || $5 > "80%" {print $1}'

done | sort | uniq
