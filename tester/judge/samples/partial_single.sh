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
NAME="TrieST"

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
r_re=0
r_tm=0
r_fa=0

# stadartizing
rm CorretorDoVictor.java
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
    idx=$(java -cp .:algs4.jar:stdlib.jar CorretorDoVictor < idxsetter.in)
    for testpath in $(find $cases/*);
    do
        testcase=$(basename $testpath)
        testcase=${testcase%.*}
        
        echo "======= $testcase ============" >> $LOG

        (time timeout --kill-after=30s 20s java -Xss1024m -Xmx1024m -Xms1024m -cp .:algs4.jar:stdlib.jar CorretorDoVictor $idx < ${testpath} > ${OUT}${testcase}.out 2>> $LOG) &>> $LOG
        run_status=$?

        sed 's/\x0//g' ${OUT}${testcase}.out > TEMPFILE
        mv -f TEMPFILE ${OUT}${testcase}.out

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
            r_ac=$(echo "$points + $r_ac" | bc)
            veredict="."
        fi

        printf $veredict
        printf $veredict >> $RES
    done;
else
    echo "COMPILATION ERROR" >> $RES
fi

printf "\n"
printf "\n" >> $RES

echo "EP: $(basename $(pwd))" >> $RES
echo "NOTA: $(echo "100*$r_ac/4000" | bc)" >> $RES
echo "CORREÇÃO AUTOMÁTICA" >> $RES
echo "$r_ac Pontos (máximo: 4000)" >> $RES
echo "$r_fa Testes com Falha no corretor (avise o monitor)" >> $RES
