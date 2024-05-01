#!/bin/bash

N=$1
sum=0
concat=""

while [ $sum -lt $N ]; do
	read string
	if test -f $string; then 
		echo $string
		K=`wc -l $string | awk '{print $1}'`
		echo $K
		sum=$((sum + $K))

		concat+=`echo " " $string`

	fi

done

cat $concat | head -n $N

