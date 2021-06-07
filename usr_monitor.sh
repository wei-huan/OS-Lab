#!/bin/bash

# 调试
# set -x

if [ $# -lt 1 ]
then
    echo "执行该脚本请输入用户名"
    exit 
fi

while true :
do 
    if  who|grep -qw $1 
    then
        echo "用户已登录"
        break
    else
        echo "用户未登录"
        sleep 5
    fi
done
