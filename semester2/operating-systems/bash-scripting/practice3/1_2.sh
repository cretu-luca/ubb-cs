#!/bin/bash

users=`cat who.fake | awk '{print $1}'`

for user in $users; do

	num=`cat ps.fake | grep -E "^$user" | wc -l`
	
	echo $user - $num 

done
