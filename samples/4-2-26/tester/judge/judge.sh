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
NAME="SAT"

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
r_tl=0
r_wa=0
r_re=0
r_tm=0
r_fa=0

# stadartizing
cp -n ${DIR}tester/judge/.gitignore . &>> $LOG
cp -n ${DIR}tester/standart/* . &>> $LOG
rm *.class
for i in *.java; do
    sed -i "s/import edu\.princeton\.cs\.algs4\..*;//g" $i
done

# compiling
make ${DIR}tester/checker/checker &>> $LOG
javac -cp .:algs4.jar:stdlib.jar *.java &>> $LOG

toexec=failed
if [ -a $NAME.class ];
then
    toexec=$NAME
fi

# judge
if [ $toexec != failed ];
then
    for testpath in $(find $cases/*);
    do
        testcase=$(basename $testpath)
        testcase=${testcase%.*}
        
        echo "======= $testcase ============" >> $LOG

        (time timeout --kill-after=30s 20s java -Xss1024m -Xmx1024m -Xms1024m -cp .:algs4.jar:stdlib.jar $toexec $2 < ${testpath} > ${OUT}${testcase}.out 2>> $LOG) &>> $LOG
        run_status=$?


        if [ $run_status -eq 124 ]
        then
            ((r_tl++))
            echo "Tempo Excedido" >> $LOG
            veredict="T"
        elif [ $run_status -eq 0 ]
        then
            checker_output=$( ${DIR}tester/checker/checker ${testpath} ${OUT}${testcase}.out ${DIR}tester/solution/answer/${testcase}.out 2>&1)
            echo $checker_output >> $LOG
            if [[ ${checker_output:0:4} == "FAIL" ]]
            then
                ((r_fa++))
                echo "FAIL" >> $LOG
                veredict="F"
            elif [[ ${checker_output:0:1} == "o" ]]
            then
                ((r_ac++))
                echo "OK" >> $LOG
                veredict="."
            else
                ((r_wa++))
                echo "Resposta Errada" >> $LOG
                veredict="W"
            fi
        else
            ((r_re++))
            echo "Erro de Execução" >> $LOG
            veredict="R"
        fi

        printf $veredict
        printf $veredict >> $RES
    done;
else
    echo "COMPILATION ERROR" >> $RES
fi

printf "\n"
printf "\n" >> $RES

echo "CORREÇÃO AUTOMÁTICA" >> $RES
echo "Quantidade de Testes | Veredito" >> $RES
echo "$r_ac | OK" >> $RES
echo "$r_tl | Tempo de Execução Excedido" >> $RES
echo "$r_wa | Resposta Errada" >> $RES
echo "$r_re | Erro de Execução" >> $RES
echo "$r_fa | Falha no corretor (avise o monitor)" >> $RES
