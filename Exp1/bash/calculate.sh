#!/bin/sh

sum=0

for i in `seq 100`
do
    sum=`expr $sum + $i`
done

echo "The total sum is $sum\n"
