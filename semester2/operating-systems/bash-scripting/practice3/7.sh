#!/bin/bash

usernames=`cat $1`
email="@scs.ubbcluj.ro"
emails=""

for username in $usernames; do

	emails=`echo $emails $username$email`,

done

echo $emails | grep -E -o ".*[^,$]"
