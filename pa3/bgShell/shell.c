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
 * @return the number of arguments [ int argc  ]
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
        fprintf(stderr, "Cannot execute %s\n", argList[0]);

        // if it doesn't exist that is the only time this error message will be invoked.
        exit(1);
    }
    // the parent process will wait for the child to finish
    else
    {
        int pid_recieved = waitpid(pid, &exitstatus, 0);
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
        else if (pid_recieved == -1)
        {
            perror("wait failed");
        }
    }
}

/**
 * @brief executes system processes in the background and redirects the output
 * to devNull
 * 
 * @param argList 
 */
void bg(char **argList, bgjob_t *process)
{
    int pid, exitstatus, bgIndex = -1;
    // make a copy of the function
    for (int i = 0; i < MAX_BG; i++)
    {
        if (process[i].pid == INVALID_PID)
        {
            bgIndex = i;
            break;
        }
    }
    // if bg index = -1 there is no open slot
    if (bgIndex == -1)
    {
        return;
    }

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
        // pipe the output to /dev/null
        int stdin_fd = open("/dev/null", O_WRONLY);
        if (stdin_fd == -1)
        {
            _exit(127);
        }
        dup2(stdin_fd, STDOUT_FILENO);
        close(stdin_fd);
        // if a program exists for the command entered, execvp will replace the rest of this block with that program.
        execvp(argList[1], &argList[1]);
        fprintf(stderr, "Cannot execute %s\n", argList[1]);

        // if it doesn't exist that is the only time this error message will be invoked.
        exit(1);
    }
    // the parent process will wait for the child to finish
    else
    {
        waitpid(pid, NULL, WNOHANG);
        process[bgIndex].pid = pid;
        strcpy(process[bgIndex].command, argList[1]);
    }
}

/**
 * @brief this function will display the list of active processes and report how many processes are active
 * 
 * @param processList 
 */
void bgList(bgjob_t *processList)
{
    // keeps track of the # active processes that are running
    int count = 0;
    // loop through the process list to check for active processes
    // and inactive processes
    for (int i = 0; i < MAX_BG; i++)
    {
        if (processList[i].pid != INVALID_PID)
        {
            printf("%d: %s\n", i, processList[i].command);
            count++;
        }
    }
    // if count in never updated print out a message to the user
    if (count == 0)
    {
        printf("There are no background processes currently running\n");
    }
    else
        // show the total amount of jobs currently running
        printf("Total Background Jobs: %d\n", count);

}

/**
 * @brief remove a process from the list
 * 
 * @param bglist an instance of the bgjob_t struct
 */
void bgKill(bgjob_t *process, char **argList)
{
    // get the pid of the requested process
    int bgIndex = strtol(argList[1], NULL, 10);

    {
        if (bgIndex < 0 || bgIndex > 4)
        {
            printf("The requested process does not exist\n");
            printf("Usage: bgkill [INDEX NUMBER] ( Where INDEX NUMBER > 0 and INDEX NUMBER < 4 )\n");
        }
        else if (process[bgIndex].pid == INVALID_PID)
        {
            printf("The requested process is no longer active\n");
        }
        else
        {
            // terminate the process
            if (kill(process[bgIndex].pid, SIGTERM) == 0)
            {
                printf("The process %d  was successfully terminated\n", bgIndex);
            }
        }
    }
}

/**
 * @brief removes any remaining processes from the bgList
 * 
 * @param bglist 
 */
void cleanBg(bgjob_t *bglist)
{
    // look for processes that are done running
    for (int i = 0; i < MAX_BG; i++)
    {
        if (waitpid(bglist[i].pid, NULL, WNOHANG) != 0)
        {
            bglist[i].pid = INVALID_PID;
        }
    }
}