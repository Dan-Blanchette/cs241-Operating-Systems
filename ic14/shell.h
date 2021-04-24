/**
 * @file shell.h
 * @author Dan Blanchette & James Lasso
 * @brief Function prototypes and macro variables for
 *        the shell program
 * @version 0.1
 * @date 2021-03-09
 * 
 */
#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h> // open

#include <sys/types.h>
#include <sys/wait.h>

#define MAX_WORDS 20
#define MAX_CMD 512

#define MAX_BG 5
#define INVALID_PID 0

typedef struct 
{
    int pid;               ///< If pid == INVALID_PID this is a free slot
    char command[MAX_CMD]; ///< The command the user entered
} bgjob_t;

int asArrayOfSubstrings(char *cmd, char **argv); 
void cleanUp(char **argv, int size);
void help();
void executeInFork(char **cmdAsArray);
void cleanBg();
void bg();
void bgList();
void bgkill();

#endif