#!/bin/bash

# Write a shell script that, for all the users in /etc/passwd, creates a file with the same name as
# the username and writes in it all the ip addresses from which that user has logged in. (hint: use
# the last command to find the ip addresses)

folder="./files"

if [ ! -d $folder ]; then
	mkdir "./files"
	echo created $folder
fi

usernames=`cat last.fake | awk '{print $1}' | sort | uniq`

for username in $usernames; do
	
	ips=`cat last.fake | awk '{print $3}' | sort | uniq`

	echo $username ip addresses > "$folder/$username.txt"
	echo "$ips" >>  "$folder/$username.txt" 
	
done
