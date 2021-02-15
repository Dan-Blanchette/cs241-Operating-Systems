/**
 * @file pa1_part1.c
 * @author Dan Blanchette
 * @brief This program will get time for the sleep command, iteration count, and name from the command line. It will then display the program's pid
 *        and loop Howdy "name" based on the desired amount of interations.
 * @date 2021-01-14
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> // required for getpid()
#include <unistd.h>    // required for sleep and getpid()

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
    int delay, iter, accu = 0, pid;

    // Name: stores a name entered from the command line
    char *name;

    // assign the current pid to variable
    pid = getpid();
    // print starting pid
    printf("Starting process %d\n", pid);
    // Error checking for incorrect amount of arguments entered.
    if (argc != 4)
    {
        usage(argv[0]);
    }
    /** assign variable to thier respective command line arguments **/

    // convert ascii strings to their respective integer values
    // based on the command line arguments entered.
    delay = atoi(argv[1]);
    iter = atoi(argv[2]);

    name = argv[3];

    // convert the integer value in seconds to milliseconds.
    delay = delay / 1000;

    while (accu < iter)
    {
        printf("Howdy %s\n", name);
        sleep(delay);
        accu = accu + 1;
    }
    // print ending pid
    printf("Ending process %d\n", pid);

    return 0;
}

//Function Definitions
void usage(char *prog_name)
{
    fprintf(stderr, "usage %s <INTEGER VALUE> <INTEGER VALUE> <NAME>\n", prog_name);
    exit(0);
}