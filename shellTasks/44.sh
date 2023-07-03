#!/bin/bash

if [ $# -ne 2 ];then
	echo Error: two arg expected
	exit 1
fi

if [ ! -f $1 ];then
	echo "not files; $0 <fail> <fail>"
	exit 2
fi

BYNARY=$1
OUTPUT=$2

touch $OUTPUT

echo "#include <stdint.h>" > $OUTPUT

ARR=""

for UINT16 in $(xxd $BINARY| cut -d" " -f2-9);do
	UINT16=$(echo $UINT16 | sed -E 's/^(..)(..)$/\2\1/')
	ARR="${ARR}0x${UINT16},"

done

ARR=$(echo $ARR| sed -E "s/,$//")

echo "uint32_t arr[] = { ${ARR} };">>$OUTPUT
