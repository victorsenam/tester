#!/bin/bash

initial=$(cd $(dirname $0) && cd .. && pwd)
cd $initial

cd grades

for aluno in $(ls);
do

    cat $aluno | head -n 80 | xsel -b
    read -p "clipboard: $aluno"
done
