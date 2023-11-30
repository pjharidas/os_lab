echo "Enter the file path:" 
read filepath 
if [ -e "$filepath" ]; then 
    file_type=$(file -b "$filepath") 
    permissions=$(stat -c "%A" "$filepath") 
    echo "File Type: $file_type" 
    echo "Permissions: $permissions" 
else 
    echo "File does not exist." 
fi 
