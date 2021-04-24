/**
 * @file shell.c
 * @author WRITE STUDENT NAME
 * @brief Function definitions for the shell program
 * @version 0.1
 * @date 2021-03-01
 * 
 */
#include "shell.h"


/**
 * @brief Creates a child process and executes the command
 *        in cmdAsArray in the child process using execvp. 
 *        Parent process is blocked until child process 
 *        terminates.
 * 
 * @param cmdAsArray  array of strings where [0] holds the 
 *                    name of the program to execute in the shell
 */
void executeInFork(char **cmdAsArray)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "Failed to fork()\n");
        return;
    }
    else if (pid == 0) // child process
    {
        execvp(cmdAsArray[0], cmdAsArray);
        fprintf(stderr, "%s: command not found\n", cmdAsArray[0]);
        _exit(127);
    }
    else // parent process
    {
        waitpid(pid, NULL, 0); // blocking
    }
}

/**
 * @brief Tokenizes *cmd* into an array of substrings stored
 *        in the output parameter *argv*.
 * 
 * @param cmd   original string command to tokenize
 * @param argv  array of C-strings
 * @return int  positive value representing number of arguments
 *              0 if argv has no strings
 */
int asArrayOfSubstrings(char *cmd, char **argv) 
{
    // make a copy of the command
    char cmdCopy[MAX_CMD];
    strcpy(cmdCopy, cmd);

    // strtok is initialize to tokenize/break cmdCopy
    // into words using " " space as delimiter
    // strtok returns the first C-string (token) 
    char* token = strtok(cmdCopy, " ");

    // while token is not NULL
    int argC = 0;
    while (token) 
    { 
        // if element in argv is not null, it means
        // its used previously and data inside needs
        // to be freed up
        if (argv[argC] != NULL)
        {
            free(argv[argC]);
        }

        // request for dynamic memory enough to store
        // the C-string in token + '\0'
        argv[argC] = (char *)malloc(sizeof(char) * (strlen(token) + 1));

        // verify if last element in token is '\n' 
        // then replace with '\0'
        if (token[strlen(token) - 1] == '\n')
        {
            token[strlen(token) - 1] = '\0'; // NULL terminate the string
        }

        // copy string 
        strncpy(argv[argC], token, strlen(token) + 1);
        // get the next token/word in cmdCopy
        token = strtok(NULL, " ");
        // increment argC to store next word 
        // in the next index of argv
        argC++;
    }

    return argC;
}

/**
 * @brief Clean up heap memory
 * 
 * @param argv  array of dynamically allocated C-strings
 * @param size  size of the array
 */
void cleanUp(char **argv, int size)
{
    for (int argC = 0; argC < size; ++argC)
    {
        if (argv[argC] != NULL)
        {
            free(argv[argC]);
        }
    }
}

/**
 * @brief Displays the help message in the shell.
 * 
 */
void help()
{
    printf("pwd  - Print the current working directory\n");
    printf("exit - Exit Shell\n");
    printf("help - Display this message\n\n");
    printf("bglist        - List background programs\n");
    printf("bgkill <int>  - Kill background process <int> int values: 1-5\n");
    printf("<UNIX cmd>    - Spawn child process, execute <UNIX cmd> in the foreground\n");
    printf("bg <UNIX cmd> - Spawn child process, execute <UNIX cmd> in the background\n\n"); 
}

void cleanBg(bgjob_t *bglist)
{
    for (int i = 0; i < MAX_BG; i++)
    {
        if (waitpid(bglist[i].pid, NULL, WNOHANG) != 0)
        {
            bglist[i].pid = INVALID_PID;
        }
    }
}

void bg()
{

}

void bgList()
{

}

void bgkill()
{

}