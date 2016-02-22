#!/bin/sh
rm -f xc xem emhello ex3
gcc -o xc -O3 -m32 -Ilinux -Iroot/lib root/bin/c.c
gcc -o xem -O3 -m32 -Ilinux -Iroot/lib root/bin/em.c -lm
./xc -o ex3 -Iroot/lib root/usr/ex/ex3.c
./xem ex3
