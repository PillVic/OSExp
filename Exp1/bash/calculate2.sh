#!/bin/bash

sum=0;

for ((i=1;i<=100;i++));
do
    sum=`expr $sum + $i`;
done
echo "The total sum is $sum."
