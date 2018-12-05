#!/usr/bin/env sh

echo $(cat $1 | tr -d '\n')|bc
