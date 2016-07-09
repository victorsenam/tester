#!/bin/bash

initial=$(cd $(dirname $0) && cd .. && pwd)
cd $initial

cd grades

for aluno in $(ls);
do

    cat $initial/helpers/trunc.txt $aluno | head -n 80 | xsel -b
    read -p "clipboard: $aluno"
done
