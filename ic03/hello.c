/**
 * @file hello.c
 * @author Dan Blanchette
 * @brief this program will print hello cs241 the number of times specified from the command line
 * @version 1
 * @date 2021-01-19 
 */

#include <stdio.h>
#include <stdlib.h>

void usage(char *program_name);

int main(int argc, char **argv)
{
    if( argc != 3)
    {
        usage(argv[0]);
    }

    int loop = atoi(argv[1]), i = 0;
    char *name = argv[2];

    for(i; i < loop; i++)
    {
        printf("Hello, %s\n", name);
    }

    return 0;
}

void usage(char *program_name)
{
    fprintf(stderr, "usage %s <INTEGER> <NAME>\n", program_name);
    exit(0);
}