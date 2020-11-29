read -p "Enter the file name-> " filename

echo $(stat -format=%b $filename)