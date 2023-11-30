#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <sys/wait.h> 
#include <unistd.h> 
#include <string.h>  
 
int main() { 
    int choice; 
 
    do {  
        printf("\nMenu:\n"); 
        printf("1. Create Child Process\n"); 
        printf("2. Write to File\n"); 
        printf("3. Read from File\n"); 
        printf("4. Change File Permissions\n"); 
        printf("5. Exit\n"); 
        printf("Enter your choice: "); 
        scanf("%d", &choice); 
 
        switch (choice) { 
            case 1: { 
                pid_t child_pid = fork(); // create a new process by forking the current 
 
                if (child_pid < 0) { 
                    return 1; 
                } else if (child_pid == 0) { 
                   
                    printf("Child process created. PID: %d\n", getpid()); 
                    exit(0); 
                } else { 
                     
                    printf("Parent process. Child PID: %d\n", child_pid); 
                    waitpid(child_pid, NULL, 0);  
                } 
                break; 
            } 
            case 2: { 
                char input[1024]; 
                printf("Enter the text to write to the file: "); 
                scanf(" %[^\n]", input); 
                int fd = open("example.txt", O_WRONLY | O_CREAT); 
                ssize_t bytes_written = write(fd, input, strlen(input)); 
                close(fd); 
                printf("Data written to file.\n"); 
                break; 
            } 
            case 3: { 
                int fd = open("example.txt", O_RDONLY); 
                char read_buffer[1024]; 
                ssize_t bytes_read = read(fd, read_buffer, sizeof(read_buffer)); 
                close(fd); 
                printf("Read from file: %.*s", (int)bytes_read, read_buffer); 
                break; 
            } 
            case 4: { 
                if (chmod("example.txt", S_IRUSR | S_IWUSR) != 0) { 
                    perror("chmod"); 
                    return 1; 
                } 
                printf("File permissions changed.\n"); 
                break; 
            } 
            case 5: 
                printf("Exiting...\n"); 
                break; 
            default: 
                printf("Invalid choice. Please choose again.\n"); 
        } 
    } while (choice != 5); 
 
    return 0; 
} 