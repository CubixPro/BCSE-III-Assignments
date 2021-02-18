#! /usr/bin/bash
read -p enter the name of the directory: file
findWord(){
    echo -n "Count of '$1': "
    echo $(grep -Rw $2 -e $1 | wc -l)
}

findWord 'int' $file
findWord 'printf' $file
findWord 'scanf' $file
