add(){
    echo "$1 + $2 = $(($1 + $2))"
    return
}
subtract(){
    echo "$1 - $2 = $(($1 - $2))"
    return
}
mul(){
    echo "$1 * $2 = $(($1*$2))"
    return
}
concatenate(){
    local concatenated_string="$1$2"
    echo "Concatenated string  $concatenated_string"
    return
}
common(){
    word1="$1"
    word2="$2"
    if [ ${#word1} -lt ${#word2} ]
    then
            word1="$2"
            word2="$1"
    fi
    for ((i=${#word2}; i>0; i--)); do
            for ((j=0; j<=${#word2}-i; j++)); do
                    if [[ $word1 =~ ${word2:j:i} ]]
                    then
                            echo "Common substring in $1 and $2 is ${word2:j:i}"
                            return
                    fi
            done
    done
}
read -p "Enter number of trials->" proceed
while [ $proceed -gt 0 ]; do
    read -p "Please enter any value-> " userv1

    read -p "Please enter any value-> " userv2

    if [[ "$userv1" =~ ^-?[0-9]+$ && "$userv2" =~ ^-?[0-9]+$ ]]; then
        add "$userv1" "$userv2"
        subtract "$userv1" "$userv2"
        mul "$userv1" "$userv2"
        echo "Concatenation not possible with integers"
        echo "Common substring extraction not possible with integers"
    elif [[ "$userv1" =~ ^-?[0-9]+$ || "$userv2" =~ ^-?[0-9]+$ ]]; then
        echo "None of given operations are possible with different-types"
    else
        echo "Addition not possible with strings"
        echo "Subtraction not possible with strings"
        echo "Multiplication not possible with strings"
        concatenate "$userv1" "$userv2"
        common "$userv1" "$userv2"
    fi

    proceed=$(($proceed -1))
done