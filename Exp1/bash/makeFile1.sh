#!bin/sh

for((i=1;i<=4;i++))
do
    fileName="m$i.txt"
    folderName="m$i"
    back=".."

    mkdir $folderName
    cd $folderName
    touch $fileName
    cd $back
done
