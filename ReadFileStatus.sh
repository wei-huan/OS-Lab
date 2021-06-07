#!/bin/bash

# 调试
# set -x

clear
echo "Please input file name:"
read filename

if [ -f $filename ]; then
    eval $(ls -l $filename| awk '{printf"filesize=%s;",$5}')
else
    echo "The file $filename not exist."
    exit
fi 

echo "filesize=$filesize"

i=0
printcount=0
newsize=0

while [ $i -lt 3 ]
do 
    sleep 3
    eval $(ls -l $filename|awk '{printf"newsize=%s;",$5}')

    if [ $newsize -ne $filesize ]; then
        echo "newsize=$newsize"
        filesize=$newsize
        printcount=`expr $printcount + 1`
    fi
    i=`expr $i + 1`
done

if [ $printcount -eq 0 ]; then
    echo "filesize no change"
fi