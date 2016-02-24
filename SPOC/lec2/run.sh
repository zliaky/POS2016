rm -f funcall
./xc -o funcall -Iroot/lib root/usr/funcall.c
./xc -s -Iroot/lib root/usr/funcall.c > funcall.txt
./xem funcall
