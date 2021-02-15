/**
 * @file   count.c
 * @author Dan Blanchette
 * @brief  Illustrate basic use of pthreads and the issue of using 
 *         unprotected shared variables:
 *         create some threads, each of which prints a message,
 *         then counts to 10,000
 * 
 *         Input:
 *            number of threads to create
 *         Output:
 *            message from each thread
 *            final total
 * 
 *         Compile: gcc -g -Wall count.c -o count -lpthread
 *         Usage: ./count <thread_count>
 * @version 0.1
 * @date    2-11-2021
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

pthread_mutex_t mutex;
sem_t semephore;
const int MAX_THREADS = 64;

// Global variables (accessible to all threads)
int thread_count;
int counter = 0;

void usage(char* prog_name);
void *count(void* rank);  // Thread function

int main(int argc, char* argv[]) 
{
    sem_init(&semephore, 0, 1);
    pthread_mutex_init(&mutex, NULL);
    // Get number of threads from command line
    if (argc != 2)
    {
        usage(argv[0]);
    }
    thread_count = strtol(argv[1], NULL, 10);
    if (thread_count <= 0 || thread_count > MAX_THREADS)
    {
        usage(argv[0]);
    }

    // Create a dynamic array to track the threads
    pthread_t *thread_handles = (pthread_t*) malloc(thread_count * sizeof(pthread_t));
    // Create a dynamic array to track thread worker number
    int *args = (int*) malloc(thread_count * sizeof(int));

    // Create the threads and start running count in each one
    for (int thread = 0; thread < thread_count; thread++) {
        args[thread] = thread;
        pthread_create(&thread_handles[thread], NULL, count, (void*) &args[thread]);
    }

    // Wait for all of the thread to finish
    for (int thread = 0; thread < thread_count; thread++) {
        pthread_join(thread_handles[thread], NULL);
    }

    free(thread_handles);
    printf("The final value of counter is %d\n", counter);
    return 0;
}  /* main */

/**
 * @brief Each thread will run this code to update counter 10000 times
 * 
 * @param  rank  thread worker number
 * @return void* null
 */
void* count(void *rank) 
{
    int my_rank = *((int*)rank); // thread worker number
    printf("Thread %d of %d starting\n", my_rank, thread_count);
    
    for(int i = 0; i < 10000; ++i)
    {
        sem_wait(&semephore);
        // pthread_mutex_lock(&mutex);
        counter++;
        // pthread_mutex_unlock(&mutex);
        sem_post(&semephore);
    } 
    printf("Thread %d of %d complete\n", my_rank, thread_count);
    return NULL;
}  /* count */

/**
 * @brief If the user gets in input parameters wrong, print a friendly
 *        message explaining how to run the program.
 * 
 * @param prog_name  name of the program
 */
void usage(char *prog_name) 
{
    fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
    fprintf(stderr, "0 < number of threads <= %d\n", MAX_THREADS);
    exit(0);
}  /* usage */