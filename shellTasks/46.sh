#!/bin/bash

if [ $# -ne 3 ];then
	echo "ERROR: $0 <number> <prefix symbol> <unit symbol>"
	exit 1
fi

if egrep -q -v '^[[:digit:]]+\.?[[:digit:]]+$' $1;then
	echo first must be a num
	exit 2
fi

if grep -v  -F ",$2," prefix.csv;then
	echo no such prefix in prefix.csv
	exit 3
fi

if grep -v -F ",$3," base.csv;then
	echo no such unit symbol in base.csv
	exit 3
fi

num=$(echo $(grep -F ",$2," ./prefix.csv |cut -d, -f3)*$1 | bc)
base=$(grep -F ",$3," ./base.csv |sed -r  's/^(.*),.*,(.*)$/(\2, \1)/')
result=$(echo $num $3 $base)

echo $result
