#!/bin/bash

tmp1='a'
tmp3='a'
tmp2=1
if [ -n $1 ] && [ -n $2 ] && [ $# = 2 ]
then
    if [ -f $1 ]
    then
        IFS=$'\n'
        for var in $(cat $1)
        do
            if [ $tmp2 = 1000 ]
            then
                if [ $tmp1 = 'z' ]
                then
                    tmp3=$( echo $tmp3 | tr '[a-z]' '[b-z]a')
                fi
                tmp1=$( echo $tmp1 | tr '[a-z]' '[b-z]a')
                tmp2=1
            fi
            echo $var >> $2$tmp3$tmp1
            tmp2=$(( tmp2 + 1 ))
        done
    else
        echo "Not file"
    fi
else
    echo "Not correct"
fi
