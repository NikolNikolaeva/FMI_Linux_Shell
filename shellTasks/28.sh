
#!/bin/bash

if [ $# -ne 2 ];then
	echo Error: two arg expected
	exit 1
fi

if [ ! -d $1 ];then 
	echo Error: fisrt arg must be dir
	exit 2
elif [[ -z  "$(ls -A $1)" ]];then
	echo empty dir
	exit 3
fi

DIR=$1
STR=$2

find $DIR -maxdepth 1 -mindepth 1 -type f | egrep  'vmlinuz\-[[:digit:]]*\.[[:digit:]]*\.[[:digit:]]*\-'$STR | sort -r -t'-' -k2 |head -1
