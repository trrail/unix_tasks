#!/bin/bash
gcc -o get_A get_A.c
gcc -o sparse sparse.c
./get_A
./sparse A B
gzip -kf A
gzip -kf B
gzip -cd B.gz | ./sparse C
./sparse A D -b 100
echo $(stat A)\\n
echo $(stat B)\\n
echo $(stat A.gz)\\n
echo $(stat B.gz)\\n
echo $(stat C)\\n
echo $(stat D)\\n
