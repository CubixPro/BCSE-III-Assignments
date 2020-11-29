findfiles() {
    echo "$1 ->" $(find "$1" -maxdepth 1 -type f | wc -l)
}
showname(){
    echo "$1\n"
}
export -f showname
export -f findfiles


echo "Total no. of files -> $(ls -lR . | egrep -c '^-')"

find ./ -type d -exec bash -c 'findfiles "$0"' {} \;

find . -type f -newerct "1 Jan 2018" ! -newerct "31 Dec 2020" -exec bash -c 'showname "$0"' {} \;