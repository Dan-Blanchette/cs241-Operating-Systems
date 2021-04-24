/**
 * @file shell.h
 * @author Dan Blanchette  
 * @brief libraries and functions header file
 * @version 0.1
 * @date 2021-02-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>   // exit
#include <unistd.h>   // fork, exec, chdir
#include <sys/wait.h> // wait
#include <ctype.h>
#include <fcntl.h> //open
#include <sys/types.h>

#define MAX_WORDS 20
#define MAX_CMD 512
#define MAX_BG 5
#define INVALID_PID 0

typedef struct
{
    int pid;
    char command[MAX_CMD];
} bgjob_t;

/* FUNCTIONS THAT RETURN A VALUE */
int cmdToArr(char *cmd, char **argList); // takes arguments from the command line and stores them in **arglist

/* FUNCTIONS THAT ARE ASSOCIATED WITH STD INPUT/OUTPUT */

void execCmd(char **argList);    // executes command line programs if they exist
void help();                                      // displays commands that can be used in the shell program
void bg(char **argList, bgjob_t *bglist); // remove "bg" and add commands to bgList
void bgList(bgjob_t *process);                    // an array of programs running in the background
void bgKill(bgjob_t *process, char **argList);    // terminate a specific process
void cleanBg(bgjob_t *processList);               // remove old processes from bgList

#endif