#!/bin/bash

[[ $# -ne 1 ]] && echo "Error: $0 <dir>" && exit 1

[[ ! -d $1 ]] && echo "$0 is not a dir" && exit 2

[[ -z $(ls -A $1) ]] && echo "$0 is empty dir" && exit 3

DIR=$1
OUTPUT=$(mktemp)
hashs=$(mktemp)

for file in $(find $DIR -type f );do

	hash=$(sha256sum $file)
	echo $hash $(stat -c %i $file) >> $hashs

done 

while read hash;do

	countAll=$(grep -F "$hash" $hashs | wc -l)
	uniqHashs=$(grep -F "$hash" $hashs | cut -d' ' -f3|sort|uniq|wc -l)

	if [ ${countAll} -eq ${uniqHashs} ];then

		grep -F "$hash" $hashs |cut -d' ' -f2 |tail -n +2 >> $OUTPUT

	elif [ ${uniqHashs} -eq 1 ];then

		grep -F "$hash" $hashs |cut -d' ' -f2 |head -n 1 >> $OUTPUT

	else

		while read inode;do

			countInodes=$(grep -F "$inode" $hashs |wc -l)

			if [ ${countInodes} -eq 1 ];then
				grep -F "$inode" $hashs | cut -d' ' -f2 >> $OUTPUT
			else
				grep -F "$inode" $hashs | cut -d' ' -f 2 | head -n 1 >> $OUTPUT
			fi

		done < <(grep -F "$hash" $hashs |cut -d' ' -f3 | sort |uniq)

	fi

done < <(cat $hashs |cut -d' ' -f1| sort |uniq) 

cat $OUTPUT

rm $hashs
rm $OUTPUT
