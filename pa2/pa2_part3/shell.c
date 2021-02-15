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
int cmdToArr(char *cmd, char **argList)
{
    int argc = 0, newString = 0;
    int length = strlen(cmd);

    for (int i = 0; i < length; ++i)
    {
        // if the command entered is not a space
        // and there has not been a recognized string
        if (cmd[i] != ' ' && newString == 0)
        {
            // a string is identified
            newString = 1; 
            // add the string to element 0 in arglist
            argList[argc] = &cmd[i];
            // increment argc to point to the next element in arglist
            ++argc;
        }
        // if the element cmd is currently pointing to is a space
        else if (cmd[i] == ' ')
        {
            // set newstring to 0
            newString = 0;
            // append a null terminator
            cmd[i] = '\0';
        }
        // return to top of loop
    }
    // append the null terminator to the argList array
    argList[argc] = NULL;
    // returns the total number of arguments that were passed
    return (argc);
}

/**
 * @brief prints out a list all commands for the shell environment
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

/**
 * @brief intereprets the command string that was entered and searches for the matching linux command
 *   if the command library exists in the usr/bin directory
 * @param argist 
 */
void execCmd(char **argList)
{
    int pid, exitstatus;
    // make a copy of the function
    pid = fork();
    // error checking
    if (pid == -1)
    {
        perror("fork failed");
        exit(1);
    }
    // child process 
    else if (pid == 0)
    {
        // if a program exists for the command entered, execvp will replace the rest of this block with that program.
        execvp(argList[0], argList);
        // if it doesn't exist that is the only time this error message will be invoked.
        fprintf(stderr, "Cannot execute %s\n", argList[0]);
        exit(1);
    }
    // the parent process will wait for the child to finish
    else
    {
        int pid_recieved = wait(&exitstatus);
        // if the child process was successful and so was the wait status, 
        // then the process ID will be shown and the exit status will be diplayed as successful.
        if (pid_recieved == pid)
        {
            if (WIFEXITED(exitstatus))
            {
                printf("***pid=%d exited with status %d***\n\n", pid, WEXITSTATUS(exitstatus));
            }
        }
        // if an error occurs during the wait status, an error message will be processed
        else if ( pid_recieved == -1)
        {
            perror("wait failed");
        }
    }
}

