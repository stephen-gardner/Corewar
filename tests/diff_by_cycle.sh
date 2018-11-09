#!/bin/bash
p1='../vm '
p2='./zaz_vm'
#echo 'enter champion file name'
#read champ
#echo $champ
champ='champions/_.cor'
dump=0
increment=1
while true; do
    $p1 $champ -d $dump | grep '0x' | grep ' : ' > out1.txt
    $p2 $champ -d $dump | grep '0x' | grep ' : ' > out2.txt
    hash1=`md5 -q out1.txt`
    hash2=`md5 -q out2.txt`
    if [ "$hash1" != "$hash2" ]; then
        echo "hashes are NOT the same at $dump    $hash1 $hash2"
        exit 1
    else
        echo "hashes are the same at $dump    $hash1 $hash2"
    fi
    rm -f out1.txt out2.txt
    dump=$(expr $dump + $increment)
done
echo $dump
