read -p "Enter the file name-> " file
read -p "Enter the string-> " string

count=0
for i in $(grep -o -n $string $file | cut -d : -f 1 | uniq -c);do
    if [ "$count" == "0" ];then
        count=$i
    else
        echo "line $i -> $count"
        count=0
    fi
done