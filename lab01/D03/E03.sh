#!/bin/sh
# lab 1 exercise 3
cd ~/ex1
rm bin/t2 test/t1
cd test
# since at some point we have to remove file text01,
# it has to be copied here again
cp text01.txt text01
ln -s text01 t1
cd ../bin
ln -s ../test/t1 t2
ln -s t2 t3
ln -s t3 t4
ln -s t4 t5
ln -s t5 t6
ln -s t6 t7
cd ..
ls -liRa
rm test/text01
cat bin/t4
rm bin/t*
