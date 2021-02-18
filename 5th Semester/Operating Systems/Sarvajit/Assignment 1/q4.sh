
for i in {1..6};do
    read -p "Enter file name-> " files[i]
done

for i in {1..6};do
    echo "Scanf count in ${files[i]}->$(grep -o -i 'scanf' ${files[i]} | wc -l)"
    echo "Printf count in ${files[i]}->$(grep -o -i 'printf' ${files[i]} | wc -l)"
    echo "Int count in ${files[i]}->$(grep -o -i 'int' ${files[i]} | wc -l)"
done