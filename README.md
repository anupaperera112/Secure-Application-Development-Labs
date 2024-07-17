"# Secure-Application-Development-Labs" 

lab1p1 to run:
first compile it ==> gcc lab1p1.c
then run it ==> ./a.out <command> + <command> + <command> + ... + <command>
ex:- ./a.out /bin/echo Linux is cool + /bin/echo But I am sleepy + /bin/echo Going to sleep now + /bin/sleep 5 + /bin/echo Now I am awake 


lab1p1 to run:
first compile it ==> gcc lab1p2.c
then run it ==> ./a.out <command> <flags> # number of sub command in %
example :- ./a.out /bin/echo % % % %
            echo Linux is cool
            But I am sleepy


approache for lab1p1:-
there are three main things that the program should do
1. get the user input
2. structure it according to a format
3. run each command in separate processess.

challenges and solutions:
1. executing commands in child process. using bellow function to run in chlid process.
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

approache for lab1p2:-
there are two main things that the program should do
1. get the arguments.
2. structure it according to a format and parallelly run the command in a child process.

challenges and solutions:
1. determine the length of the command and adjust the *arg.

    for (i = 0; i < argc - 1; i++)
    {
        if (strcmp(argv[i + 1], "%") == 0)
        {
            placeholder_count++;
        }
        args[i] = strdup(argv[i + 1]);
    }
    args[i] = NULL;

add the everything to args and then replace is accordinglly.

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

2. clean the used args after a itteration.

        for (i = 0; i < argc - 1; i++)
        {
            args[i] = strdup(argv[i + 1]);
        }
        args[i] = NULL;
