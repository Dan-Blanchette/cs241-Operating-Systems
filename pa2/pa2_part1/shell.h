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
#include <stdlib.h> // exit
#include <unistd.h> // fork, exec, chdir
#include <sys/wait.h> // wait


void execCmd(char *argList[]);
int cmdToArr(char *cmd, char *argList[]);

#endif