# IC18 - PA4 Help

### Purpose
This exercise will help you on assignment 4.

### How to Create an Unnamed Pipe
You need to use [`pipe()`](https://man7.org/linux/man-pages/man2/pipe.2.html) to create an unnamed pipe.

```cpp
#define READ  0
#define WRITE 1

int main(void)
{ 
    //==============================Do in main()
    int fd[2];

    //===============================Do in forkProducer()
    pipe(fd);
    char string[] = "Hello, world!\n";
    pid_t childpid = fork();

    if (childpid == -1)
    {
        perror("fork");
        exit(1);
    }

    if (childpid == 0)
    {
        // Child process closes up input side of pipe
        close(fd[READ]);

        // Send "string" through the output side of pipe
        write(fd[WRITE], string, (strlen(string) + 1));
        exit(0);
    }
    else
    {
        //==========================In forkProducer() close the write end of pipe and return the pid.  
        // Parent process closes up output side of pipe
        close(fd[WRITE]);
        
        //==========================This is done in runB()
        // Read in a string from the pipe
        int nbytes = read(fd[READ], readbuffer, sizeof(readbuffer));
        printf("Received string: %s", readbuffer);
    }

    return 0;
}
```

### Pre-Task
- [ ] Open **ic18.c**
- [ ] Compile program using the command below
    ```
    $ gcc -Wall ic18.c -o ic18
    ```

### Part 1:
- [ ] Create a program that parses `argv` for
    ```cpp
    int tRunTime // The time in seconds the program will run.
    int iNumProducers // The number of Producers
    int tMaxProducerSleep // The maximum sleep time between writes for a producer (In milliseconds)
    int iNumConsumers // The number of Consumers
    int tMaxConsumerSleep // The max sleep time between reads for a consumer (In milliseconds)
    ```
    
    ```
    ic18 run_time num_producers max_sleep_producer num_consumers max_sleep_consumer
    ic18 10 4 45 4 72
    ```
- [ ] Define 3 function prototypes
    ```cpp
    pid_t forkProducer(int index, int fd_p[], int tMaxSleep, const char write_char);
    pid_t forkConsumer(int index, int fd_p[], int tMaxSleep);
    void runB(time_t tStart, int iNumProducers, int iNumConsumers, int **fd_p,  int **fd_c, int tRunTime, pid_t *children);
    ```
- [ ] Get the start time of the program so that you can know when to end
    ```cpp
    #include <time.h>
    
    time_t start = time(NULL);
    ```
- [ ] Commit code

### Part 2
Use the sample code to fork the user-defined number of producers then call `runB`
- [ ] Split up the code as defined by my added comments `//==========`.
    - [ ] Define `forkProducer()` that create child processes that write a C-string to the pipe
    - [ ] Define `runB()` to have it receive inputs via the pipe

#### `forkProducer()`
- [ ] The C-string you will send in the pipe will be *two characters*. The *first* characters is the character of the producer, the *second* is the null character.
- [ ] The string will be written to the pipe infinitely.
- [ ] Sleep for a random amount of time between each write using [`usleep()`](https://man7.org/linux/man-pages/man3/usleep.3.html) and [`rand()`](https://man7.org/linux/man-pages/man3/rand.3.html),
    ```cpp
    usleep(rand() % tMaxSleep * 1000);  // Do not forget to seed the rand() function
    ```
    Here, you want **blocking** writes which is already the *default*.
- [ ] Commit code

#### `runB()`
- [ ] We should loop through each producer's pipe to read data (C-string).
- [ ] Inside the loop, check the return value of each read for the number of bytes read. If it is greater than 0, then the read was successful. Simply print out the value.
- [ ] `runB` will have an outer loop for the given number of seconds. Continue to loop and read from all of the producer's pipes until time expires.
- [ ] When time expires it should kill each of the children in turn using a `for` loop with `kill(children[i], SIGKILL);`. Remember, to use [`kill()`](https://man7.org/linux/man-pages/man2/kill.2.html), you have to include `#include <sys/wait.h>`
- [ ] In `runB` you will want **non-blocking** reads and writes, so before you enter the outer loop (timer loop) use the command below that uses [`fcntl()`](https://man7.org/linux/man-pages/man2/fcntl.2.html) for each `fd` in a `for` loop:
    ```cpp
    fcntl(fd_p[fd][0], F_SETFL, O_NONBLOCK);
    ```
- [ ] Commit code

#### `main()`
- [ ] The sample code above is for 1 pipe. You need an array of pipes that you will need to [`malloc`](https://man7.org/linux/man-pages/man3/free.3.html) since you do not know in advance how many there will be. In `main`
    ```cpp
    int **fd_p = (int **) malloc(iNumProducers * sizeof(int*)); ///< Producers
    
    for (int i = 0; i < iNumProducers; ++i)
    {
        fd_p = (int *) malloc(2 * sizeof(int));
    }
    ```
- [ ] Commit code
    
### Part 3: 
- [ ] The code below MUST be defined before any includes, otherwise you get `F_SETPIPE_SZ` undeclared
    ```cpp
    #ifndef _GNU_SOURCE
    #define _GNU_SOURCE
    #endif
    ```

- [ ] Set the size of the pipe in `forkProducer()`
    ```cpp
    // Before the fork
    int pipeSize = 32;
    
    // in child
    fcntl(fd_p[WRITE], F_SETPIPE_SZ, &pipesize);
    
    // in parent
    fcntl(fd_p[READ], F_SETPIPE_SZ, &pipesize);
    ```
- [ ] Commit code

### Part 4:
- [ ] Call your `forkProducer()` function from `main` in a `for` loop
    ```cpp
    children[i] = forkProducer(i, fd_p[i], tMaxProducerSleep, ('A' + i));
    ```
- [ ] Also, call `runB()`
- [ ] Commit code

> **IMPORTANT NOTE:** After each `printf` call,
>   ```cpp
>   fflush(stdout);
>   ```
>   This will be useful later


### Part 5: Demo to your instructor
- [ ] Show your working code to your instructor
- [ ] Commit and push the code when completed.
    ```
    $ git add ic18.c
    $ git commit -m "ic18 completed"
    $ git push
    ```
- [ ] After successfully pushing your code to Github. Verify here that the code is in Github, then submit GitHub URL in Canvas.

### Submit
- [ ] Submit GitHub URL in Canvas
