#!/bin/bash

if [ $# - ne 2 ];then
	exit 1
fi

if [ ! -d $1 ];then 
	exit 2
fi

if [ ! $2 =~ [1-9][0-9]? ];then exit 3 fi

if [[ -z $(find $1 -mindepth 1 -maxdepth 1) ]];then exit 4 fi


