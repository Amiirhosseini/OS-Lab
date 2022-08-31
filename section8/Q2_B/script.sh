#!/bin/bash

#./program $1 $2 $3


# OR

xterm -e ./server $1 $2 $3 &

sleep 2

for ((i=0;i<$3;i++))
do
        xterm -e ./client $1 $2 &
done
