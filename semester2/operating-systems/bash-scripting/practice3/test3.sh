#!/bin/bash

usernames=`cat usernames.txt`

# echo "$usernames"

IFS=$'\n'
for username in $usernames; do

	echo $username

done
