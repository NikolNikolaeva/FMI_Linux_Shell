#!/bin/bash

if [ $# -ne 2 ];then
	exit 1
fi

if [ ! -d $1 ];then
	exit 2
fi

if [ ! -z "$(ls -A $2)" ];then
	exit 3
fi

for file in $(find $1 -type f ! -name '*.swp');do

	name=$(basename $file)
	path=$(echo "${file}" | sed -E "s/^[^\/]*(\/?.*)*\/.*$/$2\1/")
	mkdir -p ./${path}
	cp $file ./${path}/
	
done
