#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COLS 20
#define MAX_LIST_SIZE 10

// {"file path", "command", NULL}

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

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        exit(1);
    }

    char *initial_command = argv[1];
    char command[100];
    int num_elements = 0;

    char **list;
    int rows = 3;  // Example: Number of rows
    int cols = 5;  // Example: Number of columns

    // Allocate memory for rows
    list = (char **)malloc(rows * sizeof(char *));
    if (list == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for each row
    for (int i = 0; i < rows; i++) {
        list[i] = (char *)malloc((MAX_COLS + 1) * sizeof(char));  // +1 for null terminator
        if (list[i] == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
    }

    while (1){

        printf("$~ ");
        fgets(command, sizeof(command), stdin);

        // Remove the trailing newline character from fgets
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "D") == 0) {
            break;
        }
        // strcpy(list[num_elements], command);
        // num_elements++;

        // Splitting the command based on spaces
        // char *token = strtok(command, " ");
        // while (token != NULL && num_elements < MAX_LIST_SIZE) {
        //     strcpy(list[num_elements], token);
        //     num_elements++;
        //     token = strtok(NULL, " ");
        // }

    }
    //     // Access and print the strings
    // for (int i = 0; i < rows; i++) {
    //     printf("list[%d]: %s\n", i, list[i]);
    // }

    // // Free allocated memory
    // for (int i = 0; i < rows; i++) {
    //     free(list[i]);
    // }
    // free(list);

    return 0;
}