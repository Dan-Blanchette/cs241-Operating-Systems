/**
 * @file    scheduler.c
 * @author  CS 241 - Operating Systems
 * @brief   This exercise will reinforce scheduling 
 *          by having you create a dispatcher program
 * @version 0.1
 * @date    2021-02-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXPROGS 5
#define MAXINSTRUCTIONS 10

// Before the program starts dispatching show the user the layout of the programs.
void printPrograms(int numberOfPrograms, int programs[MAXPROGS][MAXINSTRUCTIONS]);

// The function you must write
// Use a round-robin approach to print out a trace of the order each instruction
// will be run.
void dispatchPrograms(int numberOfPrograms, int quantum, int programs[MAXPROGS][MAXINSTRUCTIONS]);

int main(int argc, char *argv[]) 
{
    int programs[MAXPROGS][MAXINSTRUCTIONS];
    if (argc < 4)
    {
        printf("Usage: %s <number of programs> <quantum> <length of program 11> [len2] [len3] [len4] [len5]\n", argv[0]);
        printf("%s 5 3 10 10 5 7 3\n", argv[0]);
        return 1;
    }

    int numberOfPrograms = atoi(argv[1]);
    int quantum = atoi(argv[2]);

    if (numberOfPrograms > MAXPROGS)
    {
        printf("The max number of programs is %d\n", MAXPROGS);
        numberOfPrograms = MAXPROGS;
    }

    if (numberOfPrograms < 1)
    {
        printf("There must be at least one program\n");
        numberOfPrograms = 1;
    }

    if (argc < numberOfPrograms + 3)
    {
        printf("You requested %d programs but only gave lengths for %d\n", numberOfPrograms, argc - 3);
        numberOfPrograms = argc - 3;
    }

    for (int i = 0; i < numberOfPrograms; ++i)
    {
        int numberOfInstructions =  atoi(argv[3+i]);
        if (numberOfInstructions > MAXINSTRUCTIONS)
        {
            numberOfInstructions = MAXINSTRUCTIONS;
        }

        int instructionNumber = (i+1) * 0x1000;
        for (int j = 0; j < MAXINSTRUCTIONS; ++j)
        {
            programs[i][j] = 0;
            if (j<numberOfInstructions)
            {
                programs[i][j] = instructionNumber;
                instructionNumber += 4;
            }
        }
    }

    printPrograms(numberOfPrograms, programs);
    dispatchPrograms(numberOfPrograms, quantum, programs);

    return 0;
}

/**
 * @brief Show the user the layout of the programs.
 * 
 * @param numberOfPrograms  Indicates the number of processes
 * @param programs          The list of instructions in each process
 */
void printPrograms(int numberOfPrograms, int programs[MAXPROGS][MAXINSTRUCTIONS])
{
    for(int i = 0; i < numberOfPrograms; ++i)
    {
        printf("   %c  ", 'A' + i);
    }
    printf("\n");

    for(int i = 0; i < MAXINSTRUCTIONS; ++i)
    {
        for(int j = 0; j < numberOfPrograms; ++j)
        {
            printf(" %04X ", programs[j][i]);
        }
        printf("\n");
    }
}

/**
 * @brief The function you must write.
 * 
 * Use a round-robin approach to print out a trace of the order
 * each instruction will be run.
 * 
 * Each program gets quantum cycles before the next program is given control.
 * The dispatcher is at location 0100 and only has one instruction, so if quantum
 * is 3 your output should start like this:
 *   1000
 *   1004
 *   1008
 *   0100
 *   2000
 *   2004
 * NOTE: A 0 in the array indicates that there is no instruction in that slot
 * so DO NOT print it.
 * 
 * @param numberOfPrograms  Indicates the number of processes
 * @param quantum           Number of instructions that each process will execute 
 *                          before giving control back to the dispatcher
 * @param programs          The list of instructions in each process
 */
void dispatchPrograms(int numberOfPrograms, int quantum, int programs[MAXPROGS][MAXINSTRUCTIONS])
{
    int result = 0x0000;
    printf("\n");

    for(int i = 0; i < numberOfPrograms; ++i)
    {
        for(int j = 0; j < MAXINSTRUCTIONS; ++j)
        {
            if ( programs[i][j] != result )
            {
                if ( j % quantum == 0 && j != 0)
                {
                    printf("\n");
                    printf(" 0100 - Dispatcher\n");
                    printf( "\n %04X \n", programs[i][j]);
                    j = 0;
                    i++;
                }
                else
                {
                    printf("\n");
                    printf(" %04X \n", programs[i][j]);
                }
            }
        }
        
    }
}

