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
TMPOUT="judge_output.txt"
#ARGS=""
ARGS="-cp .:algs4.jar:stdlib.jar"
#ARGS="-cp .:algs4.jar:stdlib.jar -agentlib:jdwp=transport=dt_socket,address=8000,server=y,suspend=n"

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

# compiling
rm CorretorDoVictaum.java
rm Out.java
make ${DIR}tester/checker/checker &>> $LOG
cp -n ${DIR}tester/standart/* . &>> $LOG
cp -n ${DIR}tester/judge/.gitignore . &>> $LOG
rm *.class
javac $ARGS *.java &>> $LOG

toexec=failed
if [[ -f CorretorDoVictaum.class && -f WordDAG.java ]];
then
    toexec=CorretorDoVictaum
fi

# second compile method
if [ $toexec == failed ];
then
    echo "=========== TENTANDO COMPILAR DE NOVO (LevelTraversal.java -> WordDAG.java) =============" &>> $LOG

    rm *.class
    mv LevelTraversal.java WordDAG.java
    javac $ARGS *.java &>> $LOG
    
    if [[ -f CorretorDoVictaum.class && -f WordDAG.java ]];
    then
        toexec=CorretorDoVictaum
    fi
fi

# third compile method
if [ $toexec == failed ];
then
    echo "=========== TENTANDO COMPILAR DE NOVO (imports no começo do código) ==============" &>> $LOG

    rm *.class
    echo -e "import edu.princeton.cs.algs4.*;\nimport java.util.*;\n$(cat WordDAG.java)" > WordDAG.java
    javac $ARGS *.java &>> $LOG
    
    if [[ -f CorretorDoVictaum.class && -f WordDAG.java ]];
    then
        toexec=CorretorDoVictaum
    fi
fi

if [ $toexec != failed ];
then
    case_start=0
    
    for testpath in $(find $cases/*);
    do
        (time timeout --signal=SIGKILL 180s java $ARGS $toexec < $testpath 2>>$LOG > $TMPOUT) 2>> $LOG
        run_status=$?

        lines_read=-1
        case_lines=0
        case_num=$case_start

        cat $TMPOUT | while read line
        do
            ((lines_read++))
            if [[ $lines_read -le 0 ]];
            then
                continue
            fi

            if [[ ${line:0:1} == "-" ]]
            then
                curr_out=$(printf "${OUT}%03d_case.out" $case_num)
                
                cat $TMPOUT | head -n $lines_read | tail -n $case_lines > $curr_out

                ((case_num++))
                case_lines=-1
                printf "."
            fi
            ((case_lines++))
        done

        case_start=$(echo "$case_start + 100" | bc)
    done
    printf "\n"

    for casepath in $(find $OUT/*);
    do
        testcase=$(basename $casepath)
        testcase=${testcase%.*}
        veredict="F"
        
        echo "====== $testcase =========" >> $LOG
        
        if grep -q "TEMPO DE EXECUCAO EXCEDIDO" $casepath;
        then
            ((r_tl++))
            echo "Tempo Excedido" >> $LOG
            veredict="T"
        elif grep -q "TEMPO DE MONTAGEM EXCEDIDO" $casepath;
        then
            ((r_tm++))
            echo "Tempo de Montagem Excedido" >> $LOG
            veredict="M"
        elif grep -q "ERRO DE EXECUCAO" $casepath;
        then
            ((r_re++))
            echo "Erro de Execução" >> $LOG
            veredict="R"
        else
            sort ${OUT}${testcase}.out -o ${OUT}${testcase}.out
            checker_output=$( ${DIR}tester/checker/checker $testpath ${OUT}${testcase}.out ${DIR}tester/solution/answer/${testcase}.out 2>&1)
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
echo "$r_tm | Erro de Montagem (o grafo dessa query não pode ser montado)" >> $RES
echo "$r_tl | Tempo de Execução Excedido" >> $RES
echo "$r_wa | Resposta Errada" >> $RES
echo "$r_re | Erro de Execução" >> $RES
echo "Existem 26 testes, se a soma não der 26 quer dizer que houve alguma falha especial em algum teste que não foi identificada pelo corretor" >> $RES
