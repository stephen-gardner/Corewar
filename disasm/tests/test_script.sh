#!/bin/bash

for	i in subjects/*.s; do
	echo "assembling original source file: $i"
	./asm $i
	j=`echo $i | sed 's/\.s/\.cor/'`
	echo -n "md5 of assembled file: "
	md5 $j
	rm -rf reconstruct.s reconstruct.s
	echo ""
	echo "disassembling $j into 'reconstruct.s'"
	../disasm $j > reconstruct.s
	echo ".. done, assembling 'reconstruct.s'"
	./asm reconstruct.s
	echo -n "md5 of 'reconstruct.s' "
	md5 reconstruct.cor
	echo ""
	echo "press 'c' to compare source files, 'q' to quit - or - press any other key for next"
	read -rsn1 input
	if [[ "$input" = "c" ]]; then
		diff -w -y $i reconstruct.s
		echo "press any key when done"
		read -rsn1 unused
	elif [[ "$input" = "q" ]]; then
		rm -rf subjects/*.cor
		rm -rf reconstruct*
		exit
	fi
done
