#!/bin/bash

if [ $# -ne 1 ];then
	echo One arg expected
	exit 1
fi

#if [ $(id -u) -ne 0 ];then
#	echo only for root
#	exit 3
#fi

#if  cat /etc/passwd | cut -d: -f1 | egrep -q -F -v "$1" ;then 
#	echo not exist user
#	exit 2
#fi

USERp=$(ps -u $1 |wc -l)

for user in $(cat /etc/passwd |cut -d: -f1);do
 
	USER2=$(ps -u "$user" | wc -l)
	if [ $USER2 -gt $USERp ];then
		echo $user
	fi

	echo  $(ps -e -U $user -o time= | awk '{sum+=$1} END {print sum}'| date -s "%T") 

done


