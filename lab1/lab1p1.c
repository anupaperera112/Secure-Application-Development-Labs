#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_ARGS 8

void execute_command(char *command[]) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        execve(command[0], command, NULL);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);  // Wait for child process to finish
    }
    
}

int main(int argc, char *argv[]) {

    char *command[MAX_ARGS+1];  // Initialize command array
    int num_elements = 0;   // Number of elements currently in command array
    
    if (argc < 2) {
        fprintf(stderr, "Usage: %s command1 + command2 + ... + commandN\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    // /bin/echo Linux is cool + /bin/echo But I am sleepy
    for (int i = 1; i <= argc ; i++) {
        if(num_elements > MAX_ARGS){
            fprintf(stderr, "maximum args is 8");
            exit(EXIT_FAILURE);
        }

        if (argc == i || strcmp(argv[i], "+") == 0){
            command[num_elements] = NULL;

            execute_command(command);

            // Reset for the next command sequence
            num_elements = 0; 

            for (int i = 0; command[i] != NULL; i++) {
                command[i] = NULL;
            }

        }else{
            command[num_elements] = strdup(argv[i]);
            num_elements++;
        }
    }


    


    return 0;
}
