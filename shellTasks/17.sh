#!/bin/bash

#if [ "$(id -u)" -ne 0 ] ;then
#	echo "This script must be run as root"
#	exit 1
#fi

for LINE in $(cat /etc/passwd);do

old_ifs="$IFS"
IFS=:

	for arg in LINE;do
		if [ -d arg ];then
		if [ -z arg ];then
			echo "User do not have a homedir"
		elif [ ! -w arg ];then
			echo "User do not have rights for writing"
		fi
		fi

	done
	IFS="$old_ifs"

done 
