#!/bin/bash

if [ "$(id -u)" != "0" ];then
	echo only for root
	exit 1
fi

latest_file=$(find /home -type f -printf '%T@ %p\n'| sort -n|tail -1 | cut -d" " -f2)

user=$(ls -ld "$latest_file"| awk '{print $3}')

 echo  $latest_file $user
