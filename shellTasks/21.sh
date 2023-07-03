#!/bin/bash

if [ $# -ne 3 ];then
	echo Three arg needed
	exit 1
fi

if [ ! -f $1 ];then
	echo first must be file
	exit 2
elif [ -z $1 ];then 
	echo empty file
	exit 3
fi

KEY1=$2
KEY2=$3

while read -r line;do

	sed -E -i "s/($3=.*)$line (.*)/\1\2/g" $1

 done <  <( comm -2 -1  <(cat files/z1.txt | grep -F "$2=" | cut -d"=" -f2 | sed -E 's/ /\n/g'|sort) <(cat files/z1.txt | grep -F "$3=" | cut -d"=" -f2 | sed -E 's/ /\n/g'|sort))
 
