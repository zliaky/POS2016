#!/bin/sh
rm -f xc xem emhello ex2
gcc -o xc -O3 -m32 -Ilinux -Iroot/lib root/bin/c.c
gcc -o xem -O3 -m32 -Ilinux -Iroot/lib root/bin/em.c -lm
./xc -o ex2 -Iroot/lib root/usr/ex/ex2.c
./xem ex2
