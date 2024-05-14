#!/bin/bash

fname=""

while [ ! -f "$fname" ]; do
	read -p "> " fname
done
