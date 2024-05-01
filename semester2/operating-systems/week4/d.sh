#!/bin/bash

D=$1
S=$2

if ! test -d $0; then
	echo "$D is not a directory"
	exit 1
fi

for F in 'find $D -type f'; do
	N=`ls -l $F | awk '{print $5}'`
	if test $N -gt $S; then
		echo $F
	fi
done
