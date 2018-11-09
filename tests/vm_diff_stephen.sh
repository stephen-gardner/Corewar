#!/bin/bash
asm1='./zaz_asm'
vm1='./zaz_vm'
vm2='../vm'
blacklist='42.cor Car.cor barriere.cor mandragore.cor bee_gees.cor'
NC="\033[0m"
GREEN="\033[1;32m"
RED="\033[1;31m"
YELLOW="\033[1;33m"

for f in champions/*.s; do $asm1 $f; done
mkdir -p corfiles; mv champions/*.cor corfiles/ 2> /dev/null
cd corfiles; rm -f $blacklist; cd ..
idx=1
for f in corfiles/*.cor; do
    echo "--[text #$idx]--------------------------------------------------------"
    idx=$(expr $idx + 1)
    echo -n "champion $f when played alone has "
    cycles=`$vm1 -v 2 $f | grep 'It is now cycle' | tail -n 1 | sed 's/[A-Za-z ]//g'`
    echo "$cycles cycles"
    cycles=$(expr $cycles - 1)
    u='_'
    dump1="$f$u$cycles.zaz"
    dump2="$f$u$cycles.stephen"
    $vm1 -d $cycles $f | grep '0x' | grep ' : ' > $dump1
    $vm2 -d $cycles $f | grep '0x' | grep ' : ' > $dump2
    hash1=`md5 -q $dump1`
    hash2=`md5 -q $dump2`
    if [ "$hash1" = "$hash2" ]; then
        printf "$GREEN for champion $f hashes are the same at cycle $cycles $NC\n"
    else
        printf "$RED for champion $f hashes are NOT the same at cycle $cycles $NC\n"
    fi
done
