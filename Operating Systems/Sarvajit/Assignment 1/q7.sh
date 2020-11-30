echo "BCSE!!"
while [ true ];do
    read -p "Enter the command-> " com
    IFS=' ' read -ra ADDR <<< $com
    main="N/A"
    count=0
    for i in "${ADDR[@]}"; do
        ((count=count+1))
    done

    for i in "${ADDR[@]}"; do
        # process "$i"
        if [ "$main" == "N/A" ];then
            main="$i"
            if [ "$main" == "exitnewshell" ]; then
                exit

            elif [ "$main" == "editfile" -a "$count" == "1" ]; then
                vi newfile

            elif [ "$main" == "newfolder" -a "$count" == "1" ];then
                echo "folder name missing in argument!!!"

            elif [ "$main" == "info" -a "$count" == "1" ]; then
                echo "file name missing in argument!!!"

            elif [ "$main" != "exitnewshell" -a "$main" != "newfolder" -a "$main" != "info" -a "$main" != "editfile" ];then
                echo "Invalid Command!!!"
                break
            fi
        else
            if [ "$main" == "newfolder" ]; then
                mkdir $i
                echo "Folder $i created!!!"

            elif [ "$main" == "editfile" ]; then
                vi -p $i

            elif [ "$main" == "info" ]; then
                echo "Full Path-> $(pwd)/$i"
                count=0
                info[0]="info"
                for x in $(stat $i);do
                    ((count=count+1))
                    info[$count]=$x
                done
                echo "Size (in bytes)-> ${info[8]}"
                echo "Date of creation-> ${info[21]} ${info[22]},${info[24]}"
                echo "Last modification date-> ${info[17]} ${info[18]},${info[20]}"
                echo "Name of creator-> ${info[5]}"
            fi
        fi
    done
    echo "\n"
done
