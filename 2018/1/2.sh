#!/usr/bin/env sh
echo -n "1.2: "

SUM=0
for i in $(seq 1 150) ; do
	while read line; do
		SUM=$(($SUM$line))
		echo $SUM
	done < $1
done | awk 's[$0]++ {print; exit}'
