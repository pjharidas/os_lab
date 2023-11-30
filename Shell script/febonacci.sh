fibonacci() { 
    n=$1 
    a=0 
    b=1 
    echo "Fibonacci series up to $n:" 
    echo -n "$a " 
    while [ $b -le $n ]; do 
        echo -n "$b " 
        temp=$((a + b)) 
        a=$b 
        b=$temp 
    done 
    echo  
} 
read -p "Enter a number to generate Fibonacci series: " num 
fibonacci $num