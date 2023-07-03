#!/bin/bash

#if [ $(id -u) != "0" ];then
#	echo only for root
#	exit 1
#fi

users=$(ps -e -o user=| sort |uniq)

for user in $users ;do
	INFO=$(ps -u $user -o uid=,rss=|awk '{sum+=$2} END {print $user,NR,sum}') 
	echo $INFO
	if [[ "$(ps -u $user -o rss=,pid= |sort -n -k1 |tail -1|awk '{print $3}')" -gt "$(echo '2*$(echo $INFO |cut -d" " -f2)/$(echo $INFO |cut -d" " -f1)'|bc)" ]];then		
		echo $(ps -u $user -o rss=,pid= |sort -n -k1 |tail -1|awk '{print $2}') is killed
	#	kill -9 $(ps -u $user -o rss=,pid= |sort -n -k1 |tail -1|awk '{print $2}')	
	fi
	done
