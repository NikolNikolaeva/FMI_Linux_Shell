#!/bin/bash

if [[ -z $1 ]];then
	exit 2
fi

if [[ ! -d $1 ]];then
	exit 1
fi


