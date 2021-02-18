#! /usr/bin/bash

while true
do
    echo "-----------------------------------------------------"
    echo "Enter exit to exit the shell"
    echo "What do you want to enter?"
    echo "1) Number"
    echo "2) String"
    read varType

    case $varType in
    "2")
        read -p 'Enter the first string: ' word1
        read -p 'Enter the second string: ' word2

        ###########Concatenation###########

        echo -n "After concatenation: "
        word3="$word1$word2"
        echo $word3

        ###################################
        # common string
        ###################################

        if [ ${#word1} -lt ${#word2} ]
        then
            temp=$word1
            word1=$word2
            word2=$temp
        fi
        for ((i=${#word2}; i>0; i--)); do
            for ((j=0; j<=${#word2}-i; j++)); do
                if [[ $word1 =~ ${word2:j:i} ]]
                then
                        echo -n "Common Substring: "
                        echo ${word2:j:i}
                        exit
                fi
            done
        done
        ;;


    "1")
        read -p 'Enter the first variable: ' var1
        read -p 'Enter the second Variable: ' var2

        echo -n "value after addition: " 
        echo "$var1 + $var2" | bc

        echo -n "value after subtraction: " 
        echo "$var1 - $var2" | bc

        echo -n "value after multiplication: " 
        echo "$var1 * $var2" | bc

        echo -n "value after division: " 
        echo "$var1 / $var2" | bc

        echo -n "remainder after division: " 
        echo "$var1 % $var2" | bc
        ;;

    "exit")
        break
        ;;

    * )
        echo "*****Invalid Input*****"
        ;;
    esac
done



