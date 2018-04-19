#!bin/sh

cd / 
for((i=1;i<=4;i++))
do
    fileName="m$i.txt"
    folderName="m$i"
    back=".."
    touch $fileName
    mkdir $folderName
    cp $fileName $folderName/$fileName
done
