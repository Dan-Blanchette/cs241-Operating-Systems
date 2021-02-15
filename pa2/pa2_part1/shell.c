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

