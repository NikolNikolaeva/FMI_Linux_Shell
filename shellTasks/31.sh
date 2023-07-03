#!/bin/bash

if [ $# -ne 2 ];then
	echo two arg
	exit 1
fi

if [ ! -f $1 ];then
	echo first must be file
	exit 2
fi

if [ ! -d $2 ];then
	echo second must be dir
	exit 2
elif [ -n $(ls -A $2) ];then
	echo not empty dir
	exit 3
fi

DIR=$2
FILE=$1

touch ./$DIR/dict.txt

OUTPUT=./$DIR/dict.txt
number=0

while read -r line;do

	NAME=$(echo $line | cut -d: -f1 | awk '{print $1,$2}'
	echo $NAME;$number >> $OUTPUT

	touch ./$DIR/$number.txt
	cat $FILE | egrep $NAME > ./$DIR/$number.txt
	
	((number++))
done < $FILE
