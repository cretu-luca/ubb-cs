#!/bin/bash

email="@scs.ubbcluj.ro"
emails=""

prev_username=`cat $1 | head -n 1`
ddusernames=`sed 1d $1` 

emails=`echo $prev_username$email`

for username in $usernames; do

	emails=`echo $emails, $username$email`

done

echo $emails 


