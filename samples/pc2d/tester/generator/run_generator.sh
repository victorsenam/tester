#!/bin/bash

# important vars
DIR="$( cd "$( dirname "$0" )" && pwd )"
LOG="generator/generator.log"
PREFIX="generated" # generated prefix is on .gitignore

# setting starting directory
cd $DIR
cd ..

# reseting
echo "" > $LOG
rm cases/generated* &>> $LOG
mkdir cases &>> $LOG

# compiling
make generator/generator &>> $LOG
make validator/validator &>> $LOG

# counters
gen_fails=0
val_fails=0

# generation loop
case_num=0
while read line
do
    echo "Generating Case ${PREFIX}_${case_num}" &>> $LOG
    ./generator/generator $line > "cases/${PREFIX}_${case_num}.in" 2>> $LOG
    generator_status=$?
    
    if [ $generator_status -ne 0 ]
    then
        echo "Exit status $generator_status" &>> $LOG
        ((gen_fails++))
        printf "G"
    else
        printf "."
    fi

    ((case_num++))
done;
printf "\n"

# validation loop
for testcase in $(find cases/*.in);
do
    echo "Validating Case ${testcase}" &>> $LOG
    ./validator/validator < $testcase &>> $LOG
    validator_status=$?
    
    if [ $validator_status -ne 0 ]
    then
        echo "Exit status $validator_status" &>> $LOG
        ((val_fails++))
        printf "V"
    else
        printf "."
    fi
done;
printf "\n"

# output
echo "gen_fails: $gen_fails"
echo "val_fails: $val_fails"
