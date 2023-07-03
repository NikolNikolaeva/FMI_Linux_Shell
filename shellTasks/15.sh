#!/bin/bash

if [ $# -ne 1 ];then
	echo "One argument expected"
	exit 1
fi

if [ ! -d "$1" ];then
	echo not a directory
	exit 2
fi

find -L "$1" -type l  
