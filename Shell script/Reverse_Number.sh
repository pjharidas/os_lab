echo "Enter a number: "
read number
# Equivalent to line 1: read -p "Enter a number: " number

# Never give a space between = and var "var  =  6" -> wrong!
reversed=

# Notice the semi colon ;
while [ $number -gt 0 ]; 
do
 remainder=$((number % 10))
 reversed=$((reversed * 10 + remainder))
 number=$((number / 10))
done
echo "Reversed number: $reversed"
