# IC09 - PA2 Help & Using Semaphores vs Mutex to Fix `count.c`

## PA2 Help
### Purpose
This exercise will help you get started on assignment 2.

### Your Task
- [ ] Open **nicshell.c**. You may use this as the basis for PA 3.
- [ ] Update file header comment with your information and today's date
- [ ] Compile and execute the program
  ```
  $ gcc -g -Wall nicshell.c -o nicshell
  $ ./nicshell
  
  Created By: Gabe de la Cruz
  
  nicshell>
  ```
- [ ] Replace all occurences of `nic` with your own initials, and update the welcom message with your own name.

The program currently just prompts the user for input, ignores it and prompts for more until the user types exit.
- [ ] Update the system so that if the user enters `hello`, it responds with `Hi there!`
- [ ] Understand what each line of code is doing inside the `asArrayOfSubstrings()`. Also observe where this function is called in `main` and what does it do?
- [ ] If the user enters anything other than `hello` or `exit` it counts the number of words and numbers them like in the sample run below. 
  ```
  $ ./nicshell
  
  Created By: Gabe de la Cruz
  
  nicshell> hello
  Hi there!
  nicshell> the cat sat on the mat
  The string has 6 words in it:
  1. the
  2. cat
  3. sat
  4. on
  5. the
  6. mat
  nicshell> exit
  $
  ```
- [ ] Commit and push the code when completed.
  ```
  $ git add nicshell.c
  $ git commit -m "pa2 help completed"
  $ git push
  ```

## Using Semaphors to Fix `count.c`

### Purpose
Recall in IC03, we learned about **count.c** that creates some threads where each thread prints a message and then counts to 10,000. However, **count.c** has an issue of using unprotected shared variables. You will try to fix this issue in this exercise.

### Your Task
- [ ] Open **count.c** using your favorite text editing software
- [ ] Update file header comment with your information and today's date
- [ ] Include the semaphore library
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
  $ gcc -g -Wall count.c -o count -lpthread
  ```
- [ ] Run the program 5 times to confirm your code works.
  ```
  $ ./count <thread_count>
  ```
  > **NOTE:** Replace the command-line argument `<thread_count>` with a number. This number represents how many threads will be created in the **count** program.

- [ ] Test if you can also use Mutex
  - [ ] Must include `#include <pthread.h>`
  - [ ] Declare a global mutex ```pthread_mutex_t mutex;```
  - [ ] Initialize the mutex ```pthread_mutex_init(&mutex, NULL);```
  - [ ] Find the critical line of code. Put the command just before and after it.
    ```cpp
    // Locks the mutex
    pthread_mutex_lock(&mutex);
    ```
    ```cpp
    // Unlock the mutex
    pthread_mutex_unlock(&mutex);
    ```

- [ ] Commit and push the code when completed.
  ```
  $ git add count.c
  $ git commit -m "fixed race condition in count.c"
  $ git push
  ``` 
- [ ] After successfully pushing your code to Github. Verify here that the code is in Github, then in Canvas, select **true** on the last IC03 question.
