#!/bin/bash

if [ $# -ne 3 ];then 
	echo "Error: $0 <fail> <fail> <dir>"
	exit 1
fi

if [ -z $1 ] || [ -z $2 ] || [ -z $3 ];then
	exit 3
fi

if [ ! -f $1 ] || [ ! -f $2 ] || [ ! -d $3 ];then
	exit 2
fi

