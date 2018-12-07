#!/usr/bin/env sh

echo -n "1.1: "
echo $(cat $1 | tr -d '\n')|bc
