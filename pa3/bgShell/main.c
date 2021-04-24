/**
 * @file main.c
 * @author Dan Blanchette
 * @brief main file
 * @version 0.1
 * @date 2021-02-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "shell.h"

/** Global Size Values **/
#define MAXARGS 20 // Buffer size holds a maximum of 20 command line arguments
#define ARGLEN 256 // Buffer size holds a maximum of 256 chars in the argument string

int main()
{
    /** Buffers **/
    static char *argsList[MAXARGS + 1]; // fixed argument list buffer + 1 for '\0' character
    static char cmds[ARGLEN];           // fixed char array buffer

    bgjob_t bglist[MAX_BG];

    for (int i = 0; i < MAX_BG; i++)
    {
        bglist[i].pid = INVALID_PID;
    }

    // Welcome message
    printf("Created By: Dan Blanchette\nType ''help'' to see implemented commands\n\n\n");

    // get user's command input until exit is entered
    while (1)
    {
        // shell prompt
        printf("dbshell> ");
        // get the user's entries from the command line
        fgets(cmds, ARGLEN, stdin);
        // append the '\0' to the entered string
        cmds[strlen(cmds) - 1] = '\0';

        cmdToArr(cmds, argsList);

        // if the user enters "exit" close exit the shell program
        if (strcmp(argsList[0], "exit") == 0)
        {
            exit(0);
        }
        // if the user enters "help" display help options
        else if (strcmp(argsList[0], "help") == 0)
        {
            help();
        }
        else if (strcmp(argsList[0], "bg") == 0)
        {
            // calls the bg function to move processes to the background during execution
            cleanBg(bglist);
            bg(argsList, bglist);
        }
        else if (strcmp(argsList[0], "bglist") == 0)
        {
            cleanBg(bglist);
            bgList(bglist);
        }
        else if (strcmp(argsList[0], "bgkill") == 0)
        {
            cleanBg(bglist);
            bgKill(bglist, argsList);
        }
        // if the user enters a command, read the command strings in the argList until '\0' is read
        else if (*cmds != '\0')
        {
            // clean up background processes that finish
            cleanBg(bglist);

            // adds a program to the bglist, check the bglist, kill a process,
            // or run a system command.
            execCmd(argsList);
        }
    }
    return 0;
}