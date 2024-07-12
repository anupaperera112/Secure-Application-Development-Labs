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
    char line[100];
    int num_elements = 0;   // Number of elements currently in command array
    int num_command = 0;
    command = (char **)malloc((num_command + 1) * sizeof(char *));
    
    fgets(line, sizeof(line), stdin);

    // Splitting the command based on spaces
    char *token = strtok(line, " ");
    while (token != NULL) {
        // Allocate memory for the token and copy it
        if (command[num_command] == NULL) {
            command[num_command] = (char *)malloc(strlen(token) + 1);
        }
        strcpy(command[num_command], token);
        command[num_command] = (char *)realloc(command[num_command],num_elements * strlen(token) + 1);
        // command[num_command][num_elements] = strdup(token);
        num_elements++;
        token = strtok(NULL, " ");  // Get the next token
    }
    command[num_command][num_elements] = '\0';



    // Free allocated memory
    // for (int i = 0; command[i] != NULL; i++) {
    //     free(command[i]);
    // }
    free(command[num_command]);
    free(command);
    


    return 0;
}