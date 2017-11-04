cling -larmadillo -Dmain=example example.cpp
# root -e ".L /usr/lib/libarmadillo.so" -q -l -b example.cpp -e "main()" 
rm A.txt
