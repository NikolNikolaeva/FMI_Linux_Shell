#!/bin/bash

if [ $# -ne 3 ];then
	echo three param expected
	exit 1
fi

if [ ! -d $1 ] || [ ! -d $2 ];then
	echo not a dir
	exit 2
fi

if [[ ! -z $(ls -A "$2") ]];then
	echo second must be empty
	exit 3
fi

SRC=$1
DST=$2
ABC=$3

find $SRC -type f -name "*$ABC*" -exec mv {} "$DST" \;
