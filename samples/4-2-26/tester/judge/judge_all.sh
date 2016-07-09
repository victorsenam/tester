#!/bin/bash

# PARÂMETROS
# 1 - Pasta com as soluções a serem testadas
# 2 (opcional) - Regex para escolher as pastas a serem testadas

# important vars
DIR="$( cd "$( dirname "$0" )" && cd ../../ && pwd )/"
LOG="${DIR}tester/judge/judge.log"
RES="${DIR}tester/judge/judge.out"
RUNNER="${DIR}tester/judge/judge.sh"

# parameters
if [[ $# -eq 0 ]];
then
    echo "NO ARGUMENTS PROVIDED (judge_all)"
    exit 0
fi
folder=$1
pattern=${2-*/}

# going to wanted folder
cd $folder

# resetting
echo "" > $LOG
echo "" > $RES

for aluno in $pattern;
do
    echo $aluno
    time ${RUNNER} $aluno
done
