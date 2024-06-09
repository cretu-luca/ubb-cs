#!/bin/bash

# se citesc string-uri pana la stop, numaram cate incep cu vocala

count=0

while true; do
	read cuv
	if [ $cuv == "stop" ]; then
		break
	fi
	if echo "$cuvant" | grep -E -q "\<[aeiou][a-z]*\>"; then
		count=`expr $count + 1`			
	fi
done

echo $count
