#!/bin/bash

for	i in tests/subjects/*.s; do
	echo ""
	echo "---------------------------------------------------------------------------------------------------"
	echo ""
	echo "assembling original source file using zaz's assembler: $i"
	./tests/asm $i
	j=`echo $i | sed 's/\.s/\.cor/'`
	echo -n "renaming, md5 of zaz's file: "
	mv $j $j.zaz
	md5 $j.zaz

	echo ""
	echo "------------------------------------------------"
	echo ""
	echo ".. assembling using alex's assembler:"
	./asm $i
	echo -n "renaming, md5 of alex's file "
	k=`echo $i | sed 's/\.s/\.cor/'`
	mv $k $k.alex
	md5 $k.alex

	echo ""
	echo "press 'c' to compare hexdumps, 'q' to quit - or - press any other key for next"
	read -rsn1 input
	if [[ "$input" = "c" ]]; then
		rm -rf zazfile.hex alexfile.hex
		hexdump -C $j.zaz > zazfile.hex
		hexdump -C $k.alex > alexfile.hex
		diff -w -y zazfile.hex alexfile.hex
		echo "press any key when done"
		read -rsn1 unused
	elif [[ "$input" = "q" ]]; then
		rm -rf subjects/*.cor
		rm -rf zazfile.hex alexfile.hex
		exit
	fi
	rm -rf $j.zaz
	rm -rf $k.alex
	rm -rf alexfile.hex
	rm -rf zazfile.hex
done
