read -p "Enter 2 numbers : " num1 num2
echo $num1 $num2
read -p "1. Addition    
2. Subtraction      
3. Multiplication       
4. Division     
Enter your choice: " choice

case $choice in 
1) 
result=$(($num1+$num2))
;;
2) 
result=$(($num1-$num2))
;;
3) 
result=$(($num1*$num2))
;;
4) 
# [] needs to have spaces between them!
if [ $num2 -ne 0 ]; 
then
result=$(echo "scale=2; $num1 / $num2" | bc)
else 
echo "Can't divide by 0!"
exit 1
fi
;;
*)
echo "Invalid choice"
exit 1;
esac
echo "Result : $result"