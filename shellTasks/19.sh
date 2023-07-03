#!/bin/bash

if [ $# -ne 2 ];then
	echo two files expected
	exit 1
fi

if [ ! -f $1 ] || [ ! -f $2 ] ;then 
	echo not a file
	exit 2
fi

FILE1=$(grep "$1" $1 |wc -l)
FILE2=$(grep "$2" $2 |wc -l)

if [ $FILE1 -gt $FILE2 ];then
	cat $1 |cut -d'-' -f2| sort > "$1.songs"
else
	cat $2 | cut -d'-' -f2 |sort > "$2.songs"
fi
