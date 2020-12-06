#! /usr/bin/bash

echo -n "Total number of files: "
find . -type f -print | wc -l


findfiles() {
    echo "$1 has total" $(find "$1" -maxdepth 1 -type f | wc -l) "files"
}

export -f findfiles

find . -type d -exec bash -c 'findfiles "$0"' {} \;
echo "Files created b/t 2018 and 2020: "
find . -type f -newerct "1 Jan 2018" ! -newerct "31 Dec 2020";