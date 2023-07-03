#!/bin/bash

USERS=$(ps -eo user= | grep -v root)

if [ $(id -u) -eq 0 ];then
	echo only for root
	#exit 1
fi

rss_root=$(ps -u root -o rss=|awk '{sum+=$1} END{print sum}')

for user in $USERS;do 
   home_dir=$(cat /etc/passwd | grep $user | cut -d: -f6)

   if [ ! -w $home_dir ] || [ ! -d $home_dir ] || [[ $(stat -c "%U" $home_dir) != $user ]];then
	   pids=$(ps -u $user -o pid=)
	   sum_rss=$(ps -u $user -o rss=| awk '{sum+=$1} END {print sum}')

	   if [ $sum_rss -gt $rss_root ];then
	   	   for pid in $pids;do
	   	   	   echo kill $pid
	   	   	   kill -9 $pid
		   done
	   fi
   fi
done
