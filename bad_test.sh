#!/bin/bash
make
echo "Start breaking test"
echo "Just a test string" > test.txt
./main test.txt -s 1 -e &
rm -f test.txt.lck

./main test.txt -s 1 -e &
sleep 1
echo "Monday" > test.txt.lck

rm -f test.txt*
rm -f ./main
