#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int maxRepeat = 10;

    if (argc == 2)
    {
        maxRepeat = atoi(argv[1]);
    }

    for (int i = 0; i < maxRepeat; ++i)
    {
        printf("%03d Computing something...\n", i + 1);
        usleep(1000000);
    }

    return 0;
}