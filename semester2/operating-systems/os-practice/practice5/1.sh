#!/bin/bash

# Sa se scrie un script care primeste oricate cuvinte ca parametri, si citeste de 
# la tastatura incontinuu nume de fisiere. Citirea se termina atunci cand toate 
# cuvintele primite ca parametri au fost gasite in fisierele citite.

string="" # holds name files for reading 
files="" # holds names of read files 

while true; do

	read string
	
	if [ -f $string ]; then
	
		files=`echo $files $string`
	

		found_all=1
		found_word=0
	
		content=`cat $files`

		for word in $@; do

			found_word=`echo $content | grep -E -c "$word"`
		
			if [ $found_word -eq 0 ]; then
			
				found_all=0

			fi

		done

		if [ $found_all -eq 1 ]; then
	
			echo done
			exit 0

		fi
	fi

done
	
