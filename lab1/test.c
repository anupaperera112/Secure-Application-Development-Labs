#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

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

    char **command = NULL;  // Initialize command array to NULL
    int num_elements = 0;   // Number of elements currently in command array
    command = (char **)malloc((num_elements + 1) * sizeof(char *));
    
    if (argc < 2) {
        fprintf(stderr, "Usage: %s command1 + command2 + ... + commandN\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    // /bin/echo Linux is cool + /bin/echo But I am sleepy
    for (int i = 1; i <= argc ; i++) {
        if (argc == i || strcmp(argv[i], "+") == 0){
            command[num_elements] = NULL;

             execute_command(command);

            // Free dynamically allocated memory
            for (int i = 0; command[i] != NULL; i++) {
                free(command[i]);
            }
            free(command);
            // Reset for the next command sequence
            num_elements = 0; 
            command = (char **)malloc((num_elements + 1) * sizeof(char *));
        }else{
            command[num_elements] = strdup(argv[i]);
            num_elements++;
            // Resize command array
            command = (char **)realloc(command, (num_elements + 1) * sizeof(char *));
        }
    }


    


    return 0;
}
