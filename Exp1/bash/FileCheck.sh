#!/bin/sh

path="$root/$home"

cd $path

folderNumber=0
fileNumber=0


number=1
for i in $(ls)
do
    echo "$i $number"
    let number+=1
    if [ -d $i ]
    then
	let folderNumber+=1
    else
	let fileNumber+=1
    fi
done
echo "[Directory Count] "
echo "$fileNumber"
echo "[File Count] "
echo "$folderNumber"
