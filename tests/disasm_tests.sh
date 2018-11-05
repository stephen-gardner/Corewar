#!/bin/bash
asm1='./zaz_asm'
asm2='./zaz_asm'
disasm='../disasm'
ofile1='disasm_output.s'
ofile2='disasm_output.cor'

function clean_up() {
    rm -f $ofile1 $ofile2
    rm -f champions/*.cor
}

index=1
for	i in champions/*.s; do
	echo "--[disasm test #$index]----------------------------------------------------------------------"
    index=$(expr $index + 1)
	echo -n "assembling original source file: $i ... ";
    $asm1 $i > /dev/null
    echo "done";
	j=`echo $i | sed 's/\.s/\.cor/'`;
    echo -n "md5 of $j: ";
    hash1=`md5 -q $j`;
    echo $hash1;
	echo -n "disassembling $j into '$ofile1' ... ";
    $disasm $j > $ofile1;
    echo "done"
    echo -n "assembling '$ofile1' ... ";
    $asm2 $ofile1 > /dev/null
    echo "done";
	echo -n "md5 of '$ofile2' ";
    hash2=`md5 -q $ofile2`;
    echo $hash2;
    if [ "$hash1" = "$hash2" ]; then
        echo "hashes are the same"
#    	echo "----------------------------------------------------------------------------------------------"
#        diff -y -w $i $ofile1
    echo 
    else
        echo "hashes are NOT the same"
    	echo ""
    	echo "press 'c' to compare source files, 'q' to quit - or - press any other key for next"
    	read -rsn1 input
    	if [[ "$input" = "c" ]]; then
    		diff -w -y $i $ofile1
    		echo "press any key when done"
    		read -rsn1 unused
    	elif [[ "$input" = "q" ]]; then
    		clean_up
    		exit
    	fi
    fi
    clean_up
done
