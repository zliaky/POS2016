#!/bin/sh
rm -f xc xem emhello ex4
gcc -o xc -O3 -m32 -Ilinux -Iroot/lib root/bin/c.c
gcc -o xem -O3 -m32 -Ilinux -Iroot/lib root/bin/em.c -lm
./xc -o ex4 -Iroot/lib root/usr/ex/ex4.c
./xem ex4
