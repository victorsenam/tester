#!/bin/bash

rm -r output
mkdir output
make correct

for testcase in input/in*;
do
    time ./correct < $testcase > ${testcase//input\/in/output\/out}
done;
