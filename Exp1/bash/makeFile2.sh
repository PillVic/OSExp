#!bin/sh

cd /
mkdir userdata 
cd userdata

for((i=1;i<=50;i++))
do
    own="754"
    folderName="user$i"
    mkdir $folderName
    chmod $own $folderName 
done
