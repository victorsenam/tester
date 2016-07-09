#!/bin/bash

# Parâmetros
# 1 - Pasta da solução a ser testada
# 2 (opcional) - Pasta contendo os testes a serem rodados
# 3 (opcional) - Pasta contendo uma solulção válida

# important vars
DIR="$( cd "$( dirname "$0" )" && cd ../../ && pwd )/"
LOG="judge.log"
RES="judge.out"
OUT="judge_out/"
TMPOUT="judge_output.txt"

# parameters
if [[ $# -eq 0 ]];
then
    echo "NO ARGUMENTS PROVIDED"
    exit 1
fi
folder=$1
cases=${DIR}${2-'tester/cases/'}
anwsers=${DIR}${3-'tester/solution/anwser/'}

# going to wanted folder
cd $folder

# resetting
echo "" > $LOG
echo "" > $RES
rm -r $OUT &>> $LOG
mkdir $OUT &>> $LOG
r_ac=0
r_fa=0
r_ce=0

# stadartizing
rm *DoVictor.java
rm *.class
rm algs4.jar
cp -n ${DIR}tester/judge/.gitignore . &>> $LOG
cp -n ${DIR}tester/standart/* . &>> $LOG
for i in *.java; do
    sed -i "s/import edu\.princeton\.cs\.algs4\..*;//g" $i
    sed -i "s/package edu\.princeton\.cs\.algs4\..*;//g" $i
done

# compiling
make ${DIR}tester/checker/checker &>> $LOG

# judge
for testpath in $(find $cases/*);
do
    testcase=$(basename $testpath)
    testcase=${testcase%.*}
    testtype=${testcase%_*}
    
    echo "======= $testcase ============" >> $LOG
    javac -cp .:algs4.jar:stdlib.jar ${testtype}DoVictor.java &>> $LOG

    if [ -a ${testtype}DoVictor.class ];
    then
        (time timeout --kill-after=30s 20s java -Xss1024m -Xmx1024m -Xms1024m -cp .:algs4.jar:stdlib.jar ${testtype}DoVictor $2 < ${testpath} > ${OUT}${testcase}.out 2>> $LOG) &>> $LOG

        run_status=$?

        checker_output=$( ${DIR}tester/checker/checker ${testpath} ${OUT}${testcase}.out ${DIR}tester/solution/answer/${testcase}.out 2>&1)
        echo $checker_output >> $LOG
        if [[ ${checker_output:0:4} == "FAIL" ]]
        then
            ((r_fa++))
            echo "FAIL" >> $LOG
            veredict="F"
        else
            points=${checker_output:19:3}     # remove leading "partially correct ("
            points=${points%%[^[:digit:]]*}     # remove trailing non-digits
            r_ac=$(echo "0$points + $r_ac" | bc)
            veredict="."
        fi
    else
        echo "Compilation Error on $testtype" >> $LOG
        veredict="C"
        ((r_ce++))
    fi

    printf $veredict
    printf $veredict >> $RES
done;

printf "\n"
printf "\n" >> $RES

echo "EP: $(basename $(pwd))" >> $RES
echo "NOTA: $(echo "100*$r_ac/1200" | bc)" >> $RES
echo "CORREÇÃO AUTOMÁTICA" >> $RES
echo "$r_ac Pontos (máximo: 1600, dos quais 400 são bônus)" >> $RES
echo "$r_fa Testes com Falha no corretor (avise o monitor)" >> $RES
echo "$r_ce Testes com Erro de Compilação (incui o bônus)" >> $RES
