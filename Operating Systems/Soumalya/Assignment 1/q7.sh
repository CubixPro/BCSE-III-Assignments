#! /bin/bash

echo "***************************************"
echo "BCSE!!"
echo "***************************************"
while true; do

    echo "______________________________________________"
    echo "Available commands: "
    echo "1. newfolder"
    echo "2. editfile"
    echo "3. info "
    echo "4. exitnewshell"

    echo "Enter your command: "
    echo -n "Command->) "
    read -a arr
    echo "______________________________________________"

    length="${#arr[@]}"
    case $length in
        0)
            echo "No command passed!"
            ;;
        1)
            
            if [[ ${arr[0]} = 'editfile' ]];then
                echo "Opening a new File!"
                vi newTextFile
            
            elif [[ ${arr[0]} = 'info' ]]; then
                ls -l

            elif [[ ${arr[0]} = 'exitnewshell' ]]; then
                exit
            
            elif [[ ${arr[0]}=='newfolder' ]];then
                echo "Error! no folder name found!!"

            else
                echo "Invalid command! Try again!"
            fi
            ;;
        2)
            if [[ ${arr[0]} = 'editfile' && -f "${arr[1]}" ]];then
                vi ${arr[1]}
            
            elif [[ ${arr[0]} = 'info' && -f "${arr[1]}" ]]; then
                ls -l ${arr[1]}
            
            elif [[ ${arr[0]} = 'newfolder' ]]; then
                mkdir ${arr[1]}
                echo "New Folder '${arr[1]}' created!"
            
            elif [[ ${arr[0]} != 'info' && ${arr[0]} != 'editfile' ]]; then
                echo "Invalid Command! Try again!"

            else
                 echo "Invalid filename! Retry Again2"
            fi
            ;;
        *)
            echo "Too much arguments!! Retry again!!"
            ;;
    esac

   
done
