#!/bin/bash

if [ $# -ne 2 ];then
	echo "Two arg expected"
exit 1
fi

if echo $1| egrep -q -v '^[[:digit:]]+$' ||  echo $2| egrep -q -v '^[[:digit:]]+$' ;then
	echo 'Not a number'
	exit 2
fi

mkdir -p a
mkdir -p b
mkdir -p c

for FILE in $(find . -maxdepth 1 -type f);do
	if [ $(cat $FILE | wc -l ) -lt $1 ];then
		mv $FILE a
	elif [ $(cat $FILE | wc -l ) -gt $1 ] && [ $(cat $FILE | wc -l ) -lt $2 ];then
		mv $FILE b
	else
		mv $FILE c
	fi
done
