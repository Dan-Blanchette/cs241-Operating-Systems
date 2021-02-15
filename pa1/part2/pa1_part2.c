/**
 * @file pa1_part2.c
 * @author Dan Blanchette
 * @brief This program will use a for loop to immitate the sleep commmand.
 *        iteration count, and name will be provided by the command line. 
 *         It will then display the program's pid and loop Howdy "name" based on the desired amount of interations.
 * @date 2021-01-17
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> // required for getpid()
#include <unistd.h>    // required for getpid()


void usage(char *program_name);


/**
 * @brief main function
 * 
 * @param argc the number of arguments passed. Used for sentinel values and error checking
 * @param argv the argument string from the array of strings **argv that stores input from the command line.
 * @return int 
 */
int main(int argc, char **argv)
{

    // accu: accumulator
    // pid: stores program id
    // delay: number of milliseconds
    // iter: number of iterations
    int iter, accu = 0, pid;

    // Name: stores a name entered from the command line
    char *name;

    // assign the current pid to variable
    pid = getpid();
    // print starting pid
    printf("Starting process %d\n", pid);
    // Error checking for incorrect amount of arguments entered.
    if (argc != 3)
    {
        usage(argv[0]);
    }

    /* convert ascii strings to their respective integer values 
    based on the command line arguments entered. 
    */
    iter = atoi(argv[1]);
    name = argv[2];

    // convert the integer value in seconds to milliseconds.

    while (accu < iter)
    {
        printf("Howdy %s\n", name);

        // for loop imitates the sleep system call
        for (long i = 0; i < 4000000000; i++){}
        
        accu = accu + 1;
    }
    // print ending pid
    printf("Ending process %d\n", pid);

    return 0;
}

//Function Definitions

/**
 * @brief usage()
 * 
 *        provides the user with the specified format for the program to run 
 *        in the event of an error.
 * 
 * @param prog_name: argv[0]
 */
void usage(char *prog_name)
{
    fprintf(stderr, "usage %s <INTEGER VALUE> <NAME>\n", prog_name);
    exit(0);
}