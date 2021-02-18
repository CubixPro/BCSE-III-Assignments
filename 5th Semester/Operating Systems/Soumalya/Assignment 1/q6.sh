#!/bin/bash

# Assign the filename
read -p "Enter the search file name:  " search

# Assign the new filename
read -p "Enter the new file name: " new

# Take the search string
read -p "Enter the search string : " search

# Take the replace string
read -p "Enter the replace string : " replace

if [[ $search != "" && $replace != "" ]]; then
    x=$(sed "s/$search/$replace/g" $filename)
fi