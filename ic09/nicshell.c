/**
 * @file    nicshell.c
 * @author  Dan Blanchette
 * @brief   Illustrate the fgets function
 *          Prompts the user for a sentence and then counts the
 *          words and prints them numbered.
 * 
 *          Compile: gcc -g -Wall nicshell.c -o nicshell
 *          Usage:   ./nicshell
 * 
 * @version 0.1
 * @date    2-11-2021
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/wait.h>

#define MAX_WORDS 20
#define MAX_CMD 512

int asArrayOfSubstrings(char *cmd, char **argv); 
void cleanUp(char **argv, int size);

int main( void)
{
    printf("\nCreated By: Dan Blanchette\n\n");

    // Create an array of char * (C-strings) and
    // set all elements to NULL
    char *cmdAsArray[MAX_WORDS] = {NULL};

    // Loop forever until user enters "exit"
    while (1) 
    {  
        char cmd[MAX_CMD];

        printf("dbshell> "); // Print prompt
        fgets(cmd, MAX_CMD, stdin);

        if (cmd == NULL)
        {
            printf("Unrecognized Command\n");
        }

        int args = asArrayOfSubstrings(cmd, cmdAsArray); // Break the command into words

        cmdAsArray[args] = NULL;

        // the blank case
        if (cmdAsArray[0] == NULL)
        {
            // do nothing
        }
        else if (strcmp(cmdAsArray[0], "exit") == 0)
        {
            // Do other clean up
            cleanUp(cmdAsArray, MAX_WORDS);
            exit(0);
        }
        else if (strcmp(cmdAsArray[0], "hello") == 0)
            printf("Hi there!\n");
        else
        {
            printf("The string has %d words in it:\n", args);
            for (int i = 0; i < args; i++)
            {
                printf("%d. %s\n", i+1, cmdAsArray[i]);
            }
        }
    } // End while loop

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
    char* token = NULL;
    int argC = 0;
    char cmdCopy[MAX_CMD];

    strcpy(cmdCopy, cmd);
    token = strtok(cmdCopy, " ");

    while (token) 
    { 
        if (argv[argC] != NULL)
        {
            free(argv[argC]);
        }

        // tokenize cmp into the array argv
        argv[argC] = (char *)malloc(sizeof(char) * (strlen(token) + 1));

        if (token[strlen(token) - 1] == '\n')
        {
            token[strlen(token) - 1] = '\0'; // NULL terminate the string
        }

        strncpy(argv[argC], token, strlen(token) + 1);
        token = strtok(NULL, " ");
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

