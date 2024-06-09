#!/bin/bash

# Display a report showing the full name of all the users currently connected, and the number of 
# processes belonging to each of them.

users="bradu horea rares"

for user in $users; do

	processes=`grep -c "^$user" ps.fake`

	echo $user $processes


done
