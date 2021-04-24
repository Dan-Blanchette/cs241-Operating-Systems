# IC14 - PA3 Help

### Purpose
This exercise will help you on assignment 3. Use your code from assignment 2 as a starting point.

### Part 1: Update `main`
- [ ] Run the program to make sure its working
    ```
    $ make
    $ ./nicshell
    ```
- [ ] First, update file header comment with your information and today's date
- [ ] You already have special cases for if the first word is `help` or `exit`. Add 3 more for `bg`, `bglist`, and `bgkill`
- [ ] Make dummy methods for these to start with

### Part 2: Make an array for background processes
In **shell.h**, after this line in the code,
```cpp
#define MAX_CMD 512
```
- [ ] Add this definition of two more macro variables and a `struct` definition:
    ```cpp
    #define MAX_BG 5
    #define INVALID_PID 0
    
    typedef struct 
    {
        int pid;               ///< If pid == INVALID_PID this is a free slot
        char command[MAX_CMD]; ///< The command the user entered
    } bgjob_t;
    ```
- [ ] Near the top of your `main` function, declare the array
    ```cpp
    bgjob_t bglist[MAX_BG];
    ```

> **IMPORTANT NOTE:** `struct bgjob_t` is the structure to hold information about a background process. The array `bglist` is how the shell keeps track of what programs are running in the background.

### Part 3: Make a function to clean processes out of `bglist` if they have completed on their own
- [ ] Create a function that cleans up the background processes.
    - [ ] Use a `for` loop to go through each background process. Inside the loop, translate the pseudocode below into C++.
    ```
    If the background process has a VALID pid
        if (waitpid(bglist[i].pid, &status, WNOHANG) != 0)
            Set it to INVALID_PID
    ```
- [ ] A call to the function you just created should be the first step in each of the functions you created in **Part 1**. 


### Part 4: Demo to your instructor
Sketch out in your mind how you will write the functiosn you created in **Part 1**. Ask any questions you might have on how to do them.

- [ ] Show your working code to your instructor
- [ ] Commit and push the code when completed.
    ```
    $ git add main.c shell.c shell.h
    $ git commit -m "ic14 completed"
    $ git push
    ```
- [ ] After successfully pushing your code to Github. Verify here that the code is in Github, then submit GitHub URL in Canvas.


### Hint: Redirecting your output to /dev/null
```cpp
#include <fcntl.h>

// somewhere in your code
else // Child process
{
    int stdin_fd = open("/dev/null", O_WRONLY);
    if (stdin_fd == -1)
    {
        _exit(127);
    }
    dup2(stdin_fd, STDOUT_FILENO);
    close(stdin_fd);
    
    execvp(cmdAsArray[0], cmdAsArray);
    fprintf(stderr, "%s: command not found\n", cmdAsArray[0]);
    _exit(127);
}
```
* Why use `_exit()` instead of `exit()`? Read answer in [StackOverflow](https://stackoverflow.com/a/5423108)
* What is `127` in `_exit(127)`? Read about [exit codes](https://tldp.org/LDP/abs/html/exitcodes.html) with special meaning
