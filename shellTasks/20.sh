#!/bin/bash

if [ $# -ne 1 ];then
	echo one arg expected
	exit 1
fi

if [ ! -f $1 ];then
	echo not a file
	exit 2
fi

if [ -z $1 ];then
	echo empty file
	exit 3
fi

count=1

while read -r line;
do
	LINE="$count. $(echo $line| cut -d"-" -f2- )";
	echo $LINE
	count=$(echo "$count+1"|bc)
done < $1 | sort -t"." -k2

