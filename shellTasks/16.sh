#!/bin/bash

if [ $# -ne 1 ];then
	echo one parameter expected
	exit 1
fi

if echo $1|egrep -q -v "^[[:digit:]]+$" ;then
	echo not a digit 
	exit 2
fi

#if [ ! -u root ];then
#	echo only for root 
#	exit 3
#fi

for USER in $(ps -e -o user= |sort -k1 |uniq) ;do
	SUM=$(ps -e -u $USER -o pid=,rss= | awk '{sum+=$2} max<=$2 {max=$2;pid=$1} END {print sum,pid}')

	if [ $(echo $SUM | cut -d" " -f2) -gt $1 ];then

		echo "Sending SIGTERM signal to process $pid of user $user"
    	kill -9 $(echo $SUM | cut -d" " -f1)
	fi

echo "User: $USER rss-sum: $(echo $SUM | cut -d" " -f1)"
 
done



