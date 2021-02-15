/**
 * @file shell.c
 * @author Dan Blanchette
 * @brief function definitions file
 * @version 0.1
 * @date 2021-02-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "shell.h"


/**
 * @brief accepts the user's command strings and stores it in **argv
 * 
 * @param cmd the commands and flags the user enters
 * @param argList the stored string of commands 
 * @return int 
 */
int cmdToArr(char *cmd, char *argList[])
{
    int argc = 0, newString = 0;
    int length = strlen(cmd);

    for (int i = 0; i < length; ++i)
    {
        if (cmd[i] != ' ' && newString == 0)
        {
            newString = 1;
            argList[argc] = &cmd[i];
            ++argc;
        }
        else if (cmd[i] == ' ')
        {
            newString = 0;
            cmd[i] = '\0';
        }
    }
    argList[argc] = NULL;
    return (argc);
}

/**
 * @brief prints out all commands for the shell environment
 * 
 */
void help()
{
    printf("\n\npwd  - Print the current working directory\n");
    printf("exit - Exit Shell\nhelp - display this message\n\n");
    printf("bglist        - List background programs\n");
    printf("bgkill <int>  - Kill background process <int> int values: 1-5\n");
    printf("<UNIX cmd>    - Spawn child process, execute <UNIX cmd> in the foreground\n");
    printf("bg <UNIX cmd> - Spawn child process, execute <UNIX cmd> in the background\n\n\n");
}
