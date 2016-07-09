#!/bin/bash

## Isso descompacta .tar, .tar.gz e .zip
cd ..
initial=$(pwd)

rm -r result batch
mkdir result
cp -r safebatch batch

cd batch
for file in *.tar;
do
    cd "$initial/batch/"
    name=${file// /-}
    name=${name%.tar}
    mkdir "$initial/result/$name"
    mv "$file" "$initial/result/$name/"
    cd "$initial/result/$name/"

    tar -xvf "$file"
    rm "$file"
    
    count=$(ls -l | wc -l)

    if [ "$count" -eq "2" ]
    then
        dir=$(find . -mindepth 1 -maxdepth 1 -type d);
        cd "$dir"
        mv * ../
        cd ..
        rmdir "$dir"
    fi
done

cd "$initial/batch"
for file in *.tar.gz
do
    cd "$initial/batch/"
    name=${file// /-}
    name=${name%.tar.gz}
    mkdir "$initial/result/$name"
    mv "$file" "$initial/result/$name/"
    cd "$initial/result/$name/"

    tar -zvxf "$file"
    rm "$file"
    
    count=$(ls -l | wc -l)

    if [ "$count" -eq "2" ]
    then
        dir=$(find . -mindepth 1 -maxdepth 1 -type d);
        cd "$dir"
        mv * ../
        cd ..
        rmdir "$dir"
    fi
done

cd "$initial/batch"
for file in *.zip
do
    cd "$initial/batch/"
    name=${file// /-}
    name=${name%.zip}
    mkdir "$initial/result/$name"
    mv "$file" "$initial/result/$name/"
    cd "$initial/result/$name/"

    unzip "$file"
    rm "$file"
    
    count=$(ls -l | wc -l)

    if [ "$count" -eq "2" ]
    then
        dir=$(find . -mindepth 1 -maxdepth 1 -type d);
        cd "$dir"
        mv * ../
        cd ..
        rmdir "$dir"
    fi
done
