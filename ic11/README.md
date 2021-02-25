# IC11 - Mutual Exclusion `crossRoads.c`

## Using Semaphores to Fix `crossRoads.c`

### Purpose
Use semaphores to fix the attached intersection simulation.

### Your Task
- [ ] Open **crossRoads.c** using your favorite text editing software
- [ ] Update file header comment with your information and today's date
- [X] Include the semaphore library (ALREADY DONE)
  ```cpp
  #include <unistd.h>
  #include <semaphore.h>
  ```
- [ ] Declare a `semaphore` as a global variable. 
  > **NOTE:** It has to be global otherwise each thread will have its own.
  ```cpp
  sem_t semaphore;
  ```
- [ ] Initialize the `semaphore` in the `main` function BEFORE you start the threads
  ```cpp
  // Initialize semaphore, only to be used with threads
  // in this process. Set its value to 1.
  sem_init(&semaphore, 0, 1);  // What does this function do? manpages
  ```
- [ ] Find the critical line of code. Put the command just before and after it.
  ```cpp
  // Decrement the value of a sempahore if its value is greater than zero.
  // If the sempahore currently has the value zero, block here until it becomes possible
  // to perform the decrement.
  sem_wait(&semaphore); 
  ```
  
  ```cpp
  // Increments the value of a semaphore.
  // Wake up other threads/processes to check its value.
  sem_post(&semaphore);
  ```
- [ ] Compile your code
  ```
  $ gcc -g -Wall crossRoads.c -o CrossRoads -lpthread
  ```
- [ ] Demo it to your instructor with 10 south and 10 west cars without a crash
  ```
  $ ./CrossRoads 10 10
  ```

- [ ] Commit and push the code when completed.
  ```
  $ git add count.c
  $ git commit -m "intersection has zero crashes"
  $ git push
  ``` 
- [ ] After successfully pushing your code to Github. Verify here that the code is in Github, then submit GitHub URL in Canvas.
