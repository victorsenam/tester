#!/bin/bash

cd ..
initial=$(pwd)

rm -fr notas
mkdir "notas"

cd special
for aluno in */;
do
    cd "$initial/special/"
    cd "$aluno"

    echo $aluno

    for file in *.java;
    do
        cat "$initial/scripts/header.java" "$file" > "$initial/temporary_file"
        mv "$initial/temporary_file" "$file"
    done
    
    cp -r "$initial/tester/Tester.java" .
    javac-algs4 Tester.java &> "debug_log.txt"
    java-algs4 Tester &> "$initial/notas/${aluno%/}.txt"

done
