#! /usr/bin/bash

read -p "Enter the file name: " file
read -p "Enter the string name: " word

freq=$(grep -i $word $file | wc -l)

if [ $freq -gt 0 ]; then
    echo "Frequency of '$word' in $file: $freq"
else
    echo "No such word found!"
    exit
fi

# count=0
# while IFS="" read -r line || [[ -n "$line" ]]; do
#     # i have each line here
#     (( count++ ))
#     freq=0
    # echo $line
    # freq=$( $line | grep $word | wc -l)
    # declare -a arr=($line)
    # freq=0
    # for words in ${arr[@]};do
    #     if [ $word=$words ]; then
    #         (( freq++ ))
    #         # echo " HI babay....$words"
    #         # echo "Iam here $word"
    #     fi
    # done
    #     if [ $freq -gt 0 ]; then
    #         echo "line $count contains $freq occurances!"
    #     else echo "Gand mara!"
    #     fi
    #     unset arr
    #     unset freq

#     freq=$( grep -o -n $word $line | wc -l )
#     if [ freq -gt 0 ]; then
#         echo "line $count contains $freq occurances!"
#     fi

# done < "$file"


count=0
for i in $( grep -o -n $word $file | cut -d : -f 1 | uniq -c);do
    if [ "$count" == "0" ];then
        count=$i
    else
        echo "line $i -> $count"
        count=0
    fi
done


