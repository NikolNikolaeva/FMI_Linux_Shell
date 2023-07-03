#!/bin/bash

max=0
text=""

while read line;do
	text=$(echo -e "${text}\n${line}")
done
old="$IFS"
IFS="\n"
nums=""
for line in $text ;do

	if [[ $line =~ ^[+-]?[[:digit:]]+$ ]];then
		nums=$(echo -e "$nums\n$line")
		if [ $line -lt 0 ];then ((line=-line)) fi
		if [ $max -le $line ] ;then max=$line fi
	fi
done

echo "$nums" | awk -v maxNum=$max '$1<0 {curr=-$1} curr==maxNum {print $1}'|sort|uniq 

IFS="$old"
