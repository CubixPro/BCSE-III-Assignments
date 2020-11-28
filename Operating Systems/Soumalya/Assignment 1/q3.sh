#! /usr/bin/bash
file=$1
myFileSize=$(wc -c "$file" | awk '{print $1}')
echo "block size of $file is: $myFileSize"