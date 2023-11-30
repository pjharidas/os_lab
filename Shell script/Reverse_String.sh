# prompt the user to enter `string`
read -p "Enter a String : " string


# ${string}: This refers to the variable containing the string.
#: This is the operator used to find the length of the string.
length=${#string}



reversed=""


for (( i=$length-1; i>=0; i-- )); do
 reversed="${reversed}${string:$i:1}" 
 #${variable:start:length}=> String slicing 
done



echo "Reversed string: $reversed"