#!bin/sh

for((i=1;i<=50;i++))
do
    own="754"
    folderName="user$i"
    mkdir $folderName
    chmod $own $folderName 
done
