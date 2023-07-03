#!/bin/bash

if [ $# -lt 1 ] || [ $# -gt 2 ];then
	echo One or two arg expected
	exit 1
fi

if [ ! -d $1 ];then
	echo must be dir
	exit 2
fi

if [ $# -eq 2 ];then
	if echo $2| egrep -q -v '^[[:digit:]]+$';then
    	echo second must be a number
    	exit 3
	fi

	find $1 -type f -links +$(echo "$2-1"|bc) -printf "%p\n"
else

	find -L $1 -type l

fi


