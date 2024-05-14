#!/bin/bash 

# does not work

echo "$@" | sort -k=`du | awk '{print $1}'`

