#!/bin/bash

if [ $# -ne 2 ];then exit 1 fi

if [ ! -d $1 ];then exit 2 fi

if [ -d $2 ];then exit 2 fi

if [[ -z $(find $1 -maxdepth 1 -mindepth 1) ]];then exit 3 fi 

SRC=$1
DST=$2

mkdir "${DST}/images/"

FILES=$(mktemp)
find $SRC -type f -name "*.jpg" | tr -s " "|sed 's/^ *//' > $FILES

while read -r  file;do

	hesh=$(sha256sum "$file"|cut -c1-16)
	date=$(stat -c "%y" $file|cut -d' ' -f1)
	album=$(echo $file |sed -E "s/.*\((.*)\([^()]*\.jpg/\1/")
	if [ -z $album ];then album="misc" fi
	name=$(basename "$file" .jpg| sed -E "s/\ (.*\)//g")

	cp $file  "${DEST}/images/$hesh.jpg"

	ln -s ../images/$hesh.jpg $DEST/by-title/$name

done < $FILES

rm $FILES

