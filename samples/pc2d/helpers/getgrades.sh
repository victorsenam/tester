#!/bin/bash

## Isso descompacta .tar, .tar.gz e .zip
initial=$(cd $(dirname $0) && cd .. && pwd)
cd $initial

cd grades

for aluno in $(ls);
do
    xsel -b < $aluno
    read -p "clipboard: $aluno"
done
