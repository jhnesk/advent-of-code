#!/usr/bin/env sh
echo -n "1.2: "

SUM=0
while true ; do
	while read line; do
		SUM=$(($SUM$line))
		echo $SUM
	done < $1
done | awk 's[$0]++ {print; exit}'
