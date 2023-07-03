#!/bin/bash

if [ $# -ne 1 ];then
	echo "ERROR: $0 <device>"
	exit 1
fi

if [ ! -f "./wakeup" ];then
	echo file ./wakup not exist
	exit 2
fi

sed -i -r "s/(^$1 *.* *\*)enabled( *.*)/\1disabled\2/" wakeup
