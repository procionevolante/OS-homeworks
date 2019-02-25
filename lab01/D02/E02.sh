#!/bin/sh
# lab01 ex. 2
cd ~/ex1/test
cp ~/polito/OS/laface/W01/lab01/test01.txt text01.txt
cp text01.txt text01
ln text01 t1
ln t1 ../bin/t2
cd ..
ls -liRa
rm test/text01
cat bin/t2
