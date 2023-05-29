#!/bin/bash
make
echo "Start 10 tasks"
echo "Just a test string" > test.txt
echo -e "PID  lock  unlock" > result.txt
for i in {1..10}
do
  ./main test.txt -s 1 &
done

sleep 5m

echo "removing tests files"
killall -SIGINT main
rm -f test.txt
rm -f ./main
