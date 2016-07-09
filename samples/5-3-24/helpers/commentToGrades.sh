#!/bin/bash

initial=$(cd $(dirname $0) && cd .. && pwd)
cd $initial

pat=${1-'.'}

mkdir grades
cd result

for aluno in $(find $pat -maxdepth 1 -mindepth 1 -type d);
do
    cat $aluno/comment.txt $initial/helpers/warning.txt $aluno/judge.out $aluno/judge.log > $initial/grades/$(basename $aluno).txt
done
