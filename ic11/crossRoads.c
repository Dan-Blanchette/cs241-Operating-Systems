/**
 * @file   crossRoads.c
 * @author Dan Blanchette
 * @date   2/25/2021
 * @brief  The purpose of this IC is to illustrate basic use of
 *         semaphores to protect the critical section of pthreads
 *         accessing previously unprotected shared variables:
 *         Create a number of cars that want to cross an intersection
 *         of two one-way roads without any crashes.
 * 
 *         Goal for students:
 *            Find the critical section in the code below and protect 
 *            it with semaphores. Demo it to your professor before 
 *            you leave and submit it via Canvas.
 * 
 *         Input:
 *            Number of cars going South.
 *            Number of cars going West.
 * 
 *         Output:
 *            A simple animation of the progress
 *            Final count of crashes.
 * 
 *         Compile:
 *            gcc -g -Wall crossRoads.c -o CrossRoads -lpthread
 * 
 *         Usage:
 *            ./CrossRoads <South Cars> <West Cars>
 * 
 */
#include <stdio.h>  // printf
#include <unistd.h> // for usleep function
#include <stdlib.h> // exit
#include <pthread.h> 
#include <semaphore.h>

#define SLEEP_TIME 300000
#define ENTER_INTERSECTION_POINT 5
#define ENTER_WAITING_POINT 4
 
// Global variables (accessible to all threads)
sem_t printRoad, semephore;


int iSouthCars; // Number of cars left heading south 
int iWestCars;  // Number of cars left heading west 
int iWaitingSouthCar;  // Position of southern most car that has not entered the intersection.
                       //  0-3. 0 is most south.  
int iWaitingWestCar;   // Position of western most car that has not entered the intersection.
                       //  0-3. 0 is most south.  
int iIntersectionSouthCar;  // Position of southern boud car in the intersection.
                       //  0-3. 0 is most south.  -1 = not entered
int iIntersectionWestCar;   // Position of western bound car in the intersection.
                       //  0-3. 0 is most south. -1 = not entered

int progressThroughIntersection();
void* moveSouth(void *arg);
void* moveWest(void *arg);
void drawRoad();
void usage(char *prog_name);


int main(int argc, char *argv[])
{
    if (argc != 3)
    { 
        usage(argv[0]);
    }

    sem_init(&printRoad, 0, 1);
    sem_init(&semephore, 0, 1);

    // Get initial cars from command line
    iSouthCars = atoi(argv[1]);
    iWestCars = atoi(argv[2]);

    iIntersectionSouthCar = 0;
    iWaitingSouthCar = 1;
    iIntersectionWestCar = 0;
    iWaitingWestCar = 1;
    drawRoad();

    // Create the threads for each direction 
    pthread_t thread_handles[2];
    pthread_create(&thread_handles[0], NULL, moveSouth, NULL);
    pthread_create(&thread_handles[1], NULL, moveWest, NULL);

    // Wait for all of the thread to finish 
    pthread_join(thread_handles[0], NULL);
    pthread_join(thread_handles[1], NULL);

    return 0;
}


/**
 * @brief Once the car enters the intersection it is committed to
 *        going through, even if it will cause a crash.
 *        Progress the cars in both threads through the intersection.
 * 
 * @return int  number of cars that passed through the intersection
 */
int progressThroughIntersection() 
{
    int returnVal = 0;

    if (iIntersectionSouthCar) // Is there a south-bound car in the intersection? If so, move it south.
    { 
        iIntersectionSouthCar--;
        if (iIntersectionSouthCar > (ENTER_INTERSECTION_POINT - 2))
        {
            iWaitingSouthCar--; 
            returnVal += 1;
        }

        if (!iIntersectionSouthCar) // A car just left the intersection. Maybe we should do something?
        {
            sem_post(&semephore);
        }
    }

    if (iIntersectionWestCar) // Is there a west-bound car in the intersection? If so, move it west.
    { 
        iIntersectionWestCar--;
        if (iIntersectionWestCar > (ENTER_INTERSECTION_POINT - 2)) 
        {
            iWaitingWestCar--; 
            returnVal += 2;
        }

        if (!iIntersectionWestCar) // A car just left the intersection. Maybe we should do something?
        {
            sem_post(&semephore);
        }
    }
    usleep(1);
    return returnVal;
}

/**
 * @brief This is the thread to move the south bound cars.
 * 
 * @param  arg    not used in the thread function
 * @return void*  always returns NULL
 */
void* moveSouth(void *arg) 
{
    while (iSouthCars > 0 || iIntersectionSouthCar > 0)
    {
        int returnVal = progressThroughIntersection();

        // If there is a car waiting to enter the intersection let it enter.
        // What could possibly go wrong? 
        if (iSouthCars && !iIntersectionSouthCar && !iWaitingSouthCar)
        {
            iSouthCars--;
            sem_wait(&semephore);
            iIntersectionSouthCar = ENTER_INTERSECTION_POINT;
            if (iSouthCars)
            {
                iWaitingSouthCar = ENTER_WAITING_POINT;
            }
        }

        if (iWaitingSouthCar && returnVal != 1 && returnVal != 3) 
        {
            iWaitingSouthCar--;
        }
        drawRoad();
    }
    return NULL;
}

/**
 * @brief This is the thread to move the west bound cars.
 * 
 * @param  arg    not used in the thread function
 * @return void*  always returns NULL
 */
void* moveWest(void *arg) 
{
    while (iWestCars > 0 || iIntersectionWestCar > 0)
    {
        int returnVal = progressThroughIntersection();

        // If there is a car waiting to enter the intersection let it enter.
        // What could possibly go wrong? 
        if (iWestCars && !iIntersectionWestCar && !iWaitingWestCar)
        {
            iWestCars--;
            sem_wait(&semephore);
            iIntersectionWestCar = ENTER_INTERSECTION_POINT;
            if (iWestCars)
            {
                iWaitingWestCar = ENTER_WAITING_POINT;
            }
        }

        if (iWaitingWestCar && returnVal != 2 && returnVal != 3) 
        {
            iWaitingWestCar--;
        }
        drawRoad();
    }

    return NULL;
}

/**
 * @brief Draw the road at the end of each cycle. 
 *        DO NOT MODIFY THIS CODE!
 */
void drawRoad()
{
    static int crashes = 0; // The number of crashes so far.
    int bSouth = 0; // A boolean set to 2 if there is a southboud car in the cross point.
    int iEmptySpot; // a temproarry variable to defines the space between two cars 

    sem_wait(&printRoad); // Ensure that we are not in the middle of a print.
    for (int i = 0; i < 50; i ++) 
    {
        printf("\n"); // jump to bottom of console
    }

    if (iSouthCars > 1)
    {
        printf("and %d more.", iSouthCars - 1);
    }

    if (iSouthCars == 0) 
    {
        for (int i = 0; i < 2; i ++) 
        {
            printf("\n   #"); 
        }

        if (iIntersectionSouthCar > (ENTER_INTERSECTION_POINT - 1))
        {   
            printf("\n | #");
        } 
        else
        {   
            printf("\n   #");
        } 

        if (iIntersectionSouthCar > (ENTER_INTERSECTION_POINT - 2))
        {   
            printf("\n | #");
        } 
        else
        {   
            printf("\n   #");
        } 
    }
    else 
    { 
        iEmptySpot = 4 - iWaitingSouthCar;
        if (iEmptySpot == 4) 
        { 
            iEmptySpot = 0;
        }

        for (int j = 0; j < 4; j ++) 
        {
            if (j == iEmptySpot)
            {
                printf("\n   #");
            }
            else
            {
                printf("\n | #");
            }
        }
    }
    printf("###\n");

    if (iIntersectionSouthCar > (ENTER_INTERSECTION_POINT - 3) && iIntersectionSouthCar < (ENTER_INTERSECTION_POINT + 1))
    {   
        printf(" | \n");
    } 
    else
    {   
        printf("\n");
    }

    if (iIntersectionSouthCar > (ENTER_INTERSECTION_POINT - 4) && iIntersectionSouthCar < (ENTER_INTERSECTION_POINT + 0))
    {   
        bSouth = 1;
    } 
    else
    {   
        bSouth = 0;
    }

    ///////////////Print West/////////////////////////////////

    if (iIntersectionWestCar > 0 && iIntersectionWestCar < (ENTER_INTERSECTION_POINT - 1))
    {   
        printf("-");
    } 
    else
    {   
        printf(" ");
    }

    if (iIntersectionWestCar > 1 && iIntersectionWestCar < (ENTER_INTERSECTION_POINT - 0))
    {   
        if (bSouth) 
        {
            printf("+"); 
            crashes++;
        } 
        else 
        {
            printf("-");
        }
    } 
    else
    {   
        if (bSouth) 
        {
            printf("|"); 
        }
        else 
        {
            printf(" ");
        }
    } 

    if (iIntersectionWestCar > 2 && iIntersectionWestCar < (ENTER_INTERSECTION_POINT + 1))
    {   
        printf("-");
    } 
    else
    {   
        printf(" ");
    }

    if (iWestCars == 0) 
    {
        if (iIntersectionWestCar > (ENTER_INTERSECTION_POINT - 2))
        {   
            printf("-");
        } 
        else
        {   
            printf(" ");
        } 

        if (iIntersectionWestCar  > (ENTER_INTERSECTION_POINT - 1))
        {   
            printf("-");
        } 
        else
        {   
            printf(" ");
        } 
    }
    else 
    { 
        iEmptySpot = iWaitingWestCar - 1;

        if (iEmptySpot == -1) 
        { 
            iEmptySpot = 3;
        }

        for (int j = 0; j < 3; j ++) 
        {
            if (j == iEmptySpot)
            {
                printf(" ");
            }
            else
            {
                printf("-");
            }
        }
    }

    if (iWestCars > 1)
    {
        printf(" and %d more.", iWestCars - 1);
    }

    printf("\n");

    ///////////////////////////////////////////////////////////////

    if (iIntersectionSouthCar > ENTER_INTERSECTION_POINT-5 && iIntersectionSouthCar < (ENTER_INTERSECTION_POINT - 1))
    {   
        printf(" | \n");
    } 
    else
    {   
        printf("\n");
    }

    printf("Crashes %d \n", crashes);
    sem_post(&printRoad);
    usleep(SLEEP_TIME);
    // getchar();
}

/**
 * @brief If the user gets the input parameters wrong, print a
 *        friendly message explaining how to run the program.
 * 
 * @param prog_name name of the program
 */
void usage(char *prog_name) 
{
    fprintf(stderr, "usage: %s <South Cars> <West Cars>\n", prog_name);
    fprintf(stderr, "usage: %s 20 15\n", prog_name);
    exit(0);
}  