#!/bin/bash

zaz_asm='./zaz_asm'
zaz_ext='.zaz'
alex_asm='../asm'
alex_ext='.alex'
hd_ext='.hexdump'

function clean_up() {
    rm -rf champions/*.cor.*
    rm -rf *$hd_ext
}

index=1

for i in champions/*.s; do
    echo "--[asm test #$index]-------------------------------------------------------------------------"
    index=$(expr $index + 1)
    echo "assembling original source file using zaz's assembler: $i"
    $zaz_asm $i
    j=`echo $i | sed 's/\.s/\.cor/'`
    echo -n "renaming, md5 of file assembled with zaz-asm: "
    mv $j $j$zaz_ext
    zaz_md5=`md5 -q $j$zaz_ext`
    echo $zaz_md5
    echo ".. assembling using alex's assembler:"
    $alex_asm $i
    echo -n "renaming, md5 of file assembled with alex-asm: "
    k=`echo $i | sed 's/\.s/\.cor/'`
    mv $k $k$alex_ext
    alex_md5=`md5 -q $k$alex_ext`
    echo $alex_md5
    if [ "$zaz_md5" = "$alex_md5" ]; then
        echo "md5 hashes are the same"
    else
        echo $zaz_md5
        echo $alex_md5
        echo "md5 hashes are NOT the same"
        echo ""
        echo "press 'c' to compare hexdumps, 'q' to quit - or - press any other key for next"
        read -rsn1 input
        if [[ "$input" = "c" ]]; then
            rm -rf zazfile.hex alexfile.hex
            f1=$j$zaz_ext$hd_ext
            hexdump -C $j$zaz_ext > $f1
            f2=$k$alex_ext$hd_ext
            hexdump -C $k$alex_ext > $f2
            diff -w -y $f1 $f2
            echo "press any key when done"
            read -rsn1 unused
        elif [[ "$input" = "q" ]]; then
            clean_up
            exit
        fi
            clean_up
    fi
    clean_up
done
