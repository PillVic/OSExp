#!/bin/sh

sum=0
i=0
while [ $i -le 100 ]
do
    sum=`expr $sum + $i`
    i=`expr $i + 1`
done

echo "The total sum is $sum."
