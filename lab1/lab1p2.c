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
    char *args[MAX_ARGS + 1];
    char input_line[MAX_LINE_LENGTH];
    int placeholder_count = 0;
    int i;   

    for (i = 0; i < argc - 1; i++)
    {
        if (strcmp(argv[i + 1], "%") == 0)
        {
            placeholder_count++;
        }
        args[i] = strdup(argv[i + 1]);
    }
    args[i] = NULL;

    if(placeholder_count == 0)
    {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if(placeholder_count>MAX_ARGS)
    {
        fprintf(stderr, "maximum number of input words is 8\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(input_line, sizeof(input_line), stdin) != NULL)
    {
        input_line[strcspn(input_line, "\n")] = '\0';
        char *tokens[MAX_ARGS];
        int token_count = 0;
        char *token = strtok(input_line, " ");
        while (token != NULL && token_count < MAX_ARGS)
        {
            tokens[token_count++] = token;
            token = strtok(NULL, " ");
        }
        int arg_index = 0;
        int token_index = 0;
        for (i = 0; i < argc - 1; i++)
        {
            if (strcmp(args[arg_index], "%") == 0)
            {
                if (token_index < token_count)
                {
                    args[arg_index] = tokens[token_index];
                    token_index++;
                }
                else
                {
                    args[arg_index] = NULL;
                }
            }
            arg_index++;
        }
        args[arg_index] = NULL;

        execute_command(args);

        for (i = 0; i < argc - 1; i++)
        {
            args[i] = strdup(argv[i + 1]);
        }
        args[i] = NULL;
    }

    return 0;
}