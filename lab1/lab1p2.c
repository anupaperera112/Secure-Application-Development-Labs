#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_ARGS 8
#define MAX_LINE_LENGTH 128

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

    char *command = NULL;  // Initialize command array to NULL
    char line[MAX_LINE_LENGTH];
    int num_elements = 0;   // Number of elements currently in command array
    command = (int *)malloc((num_elements + 1) * sizeof(int *));

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        exit(1);
    }

    while (fgets(line, sizeof(line), stdin) != NULL){
        command[num_elements] = strdup(argv[1]);
        char *token = strtok(line, " ");
        while (token != NULL) {
            num_elements++;
            command = (int *)realloc(command, (num_elements + 1) * sizeof(int *));
            command[num_elements] = strdup(token);
            token = strtok(NULL, " ");  // Get the next token
        }
        command[num_elements] = NULL;
        execute_command(*command);
        num_elements = 0;
    }
    
    return 0;
}