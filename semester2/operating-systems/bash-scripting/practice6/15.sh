#!/bin/bash

# 15. Calculate the average of all process ids in the system per user

ps_info=`cat ps.fake`
users=`echo "$ps_info" | awk '{print $1}' | sort | uniq`

for user in $users; do

	sum=0
	pids=`echo "$ps_info" | grep "^$user" | awk '{print $2}'`
	count=`echo "$pids" | wc -l`

	for pid in $pids; do
		
		sum=$((sum+pid))

	done
	
	sum=$((sum/count))
	

	echo $user $sum


done
