calculate_factorial() { 
    local n=$1 
    local result=1 
    while [ $n -gt 0 ]; do 
        result=$((result * n)) 
        n=$((n - 1)) 
    done 
    echo $result 
} 
echo "Enter a number: " 
read number 
factorial=$(calculate_factorial $number) 
echo "Factorial of $number is: $factorial"