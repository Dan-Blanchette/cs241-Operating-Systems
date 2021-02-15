/**
 * @file main.c
 * @author Dan Blanchette
 * @brief main file
 * @version 0.1
 * @date 2021-02-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "shell.h"

#define MAXARGS 20
#define ARGLEN 256

int main()
{
    char *argsList[MAXARGS+1];
    char cmds[ARGLEN];


    printf("Created By: Dan Blanchette\nType ''help'' to see implemented commands\n\n\n");
    // get user's command input until exit is entered
    while(1)
    {
        printf("dbshell>");
        fgets(cmds, ARGLEN, stdin);

        cmds[strlen(cmds) - 1] = '\0';
        
        // if the user enters "exit" close exit the shell program
        if(strcmp(cmds, "exit") == 0)
        {
            exit(0);
        }
        else if(strcmp(cmds, "help") == 0)
        {
            help();
        }
    }

    return 0;
}