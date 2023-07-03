#!/bin/bash

if [ $# -ne 2 ];then
	echo "Two arg needed"
	exit 1
fi

if [ ! -f $1 ];then
	echo "Files expected"
	exit 2
fi

FILE=$1
LINES=$(cat $FILE | cut -d, -f2-,1| sort)
LINES_withot_id=<(cat $FILE | cut -d',' -f"2-"|sort|uniq)

touch $2

while read -r line;do
	
	result=$(egrep -E $line $FILE | sort -n -t, -k1|tail -1) 
	echo $result\ >> $2
done < <(cat $FILE|cut -d',' -f"2-"|sort|uniq)


