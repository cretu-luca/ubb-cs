#!/bin/bash

ps_info=`cat ps.fake`
users=`cat ps.fake | awk '{print $1}' | sort | uniq`


for user in $users; do
	
	sum=0
	pids=`cat ps.fake | grep "^$user" | awk '{print $2}'` 
	count=`echo "$pids" | wc -l`

	for pid in $pids; do

		sum=$((sum+pid))

	done
	
	sum=$((sum/count))

	echo average for $user is $sum

done
