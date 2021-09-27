#!/bin/bash

re='^[0-9]+$'

if [[ -z $1 ]]
then
    echo "parametrs not found"
elif [[ $1 =~ $re ]]
then   
    echo "Name: " $( basename $(readlink -nf $0))
    echo "Pid: "$1
    echo "PPid: " $(ps -o ppid= -p $1)

    if [[ "fd" == $2 ]]
    then
        while read -r line
        do
            echo fd = $line
        done <<< $(ls  /proc/$1/fd/)
    fi
else
    echo pid = "$1 process not found"
fi