#!/bin/bash

if [ $# -lt 1 ] || [ $# -gt 2 ];then
	echo one or two arg 
	exit 1
fi

if [ ! -d $1 ];then
	echo must be dir
	exit 2
fi

FILE=""

if [ $# -eq 2 ];then
	if [ ! -f  $2 ];then
		echo not a file
		exit 3
	fi
	FILE=$2
fi

DIR=$1
BROKEN=$(find -L $DIR -type l)
RESULT=""
while read -r line ; do
	
	if [ ! -z "$(echo $line|cut -d" " -f3)" ]  ;then
		RESULT="$RESULT$line\n"
	fi
	
done < <(find $DIR -type l -printf "%p -> %l\n")
RESULT="$RESULT Boken:$($BROKEN|wc  -l)"
if [ ! -z $FILE ];then
	 echo -e $RESULT > $FILE
	exit 0
fi

echo -e $RESULT
