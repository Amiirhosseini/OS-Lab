#!/bin/bash

if [ "$1" == "-r" ]; then
	cat $2
fi

if [ "$1" == "-m" ]; then
	mkdir $2

	for ((i=$5;i<=$6;i++))
	do
        touch /$2/$3$i.$4
	done
fi

