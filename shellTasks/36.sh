#!/bin/bash

if [ $# - ne 2 ];then
	exit 1
fi

if [ ! -f $1 ];then
	exit 2
fi

if [ ! -d $2 ];then
	exit 3
fi


