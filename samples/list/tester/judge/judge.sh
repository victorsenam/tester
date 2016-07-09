#!/bin/bash

# Parâmetros
# 1 - Pasta da solução a ser testada
# 2 (opcional) - Pasta contendo os testes a serem rodados
# 3 (opcional) - Pasta contendo uma solulção válida

# important vars
DIR="$( cd "$( dirname "$0" )" && cd ../../ && pwd )/"
LOG="judge.log"
RES="judge.out"
OUT="judge_output/"

# parameters
if [[ $# -eq 0 ]];
then
    echo "NO ARGUMENTS PROVIDED"
    exit 1
fi
folder=$1
cases=${DIR}${3-'tester/cases/'}
anwsers=${DIR}${4-'tester/solution/anwser/'}

# going to wanted folder
cd $folder

# resetting
echo "" > $LOG
echo "" > $RES
mkdir $OUT &>> $LOG
r_ac=0
r_tl=0
r_wa=0
r_re=0

# compiling
make ${DIR}tester/checker/checker &>> $LOG
cp -n ${DIR}tester/standart/* . &>> $LOG
cp -n ${DIR}tester/judge/.gitignore . &>> $LOG
rm *.class
javac -cp .:algs4.jar:stdlib.jar *.java &>> $LOG

toexec=failed
if [ -a CorretorDoVictor.class ];
then
    toexec=CorretorDoVictor
fi

# second compile method
# if [ $toexec == failed ];
if [ 1 == 0 ];
then
    echo "Second Compile Method" &>> $LOG

    rm *.class
    echo -e "import edu.princeton.cs.algs4.*;\nimport java.util.*;\n$(cat List.java)" > List.java
    javac -cp .:algs4.jar:stdlib.jar *.java &>> $LOG
    
    if [ -a MyTester.class ];
    then
        toexec=MyTester
    fi
fi

if [ $toexec != failed ];
then
    for testpath in $(find $cases/*);
    do
        testcase=$(basename $testpath)
        testcase=${testcase%.*}
        
        echo "======= $testcase ============" >> $LOG

        (time timeout --kill-after=25s 20s java -cp .:algs4.jar:stdlib.jar $toexec $2 < ${testpath} > ${OUT}${testcase}.out 2>> $LOG) &>> $LOG
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
            if [[ ${checker_output:0:1} == "o" ]]
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
    echo "FAILED COMPILE" >> $LOG
fi
printf "\n"
printf "\n" >> $RES

echo "CORREÇÃO AUTOMÁTICA" >> $RES
echo "Quantidade de Testes | Veredito" >> $RES
echo "$r_ac | OK" >> $RES
echo "$r_tl | Tempo de Execução Excedido" >> $RES
echo "$r_wa | Resposta Errada" >> $RES
echo "$r_re | Erro de Execução" >> $RES
