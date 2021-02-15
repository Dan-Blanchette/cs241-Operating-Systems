# Programming Assignment 1

**Purpose:** Use Linux/UNIX system calls to do some very basic process operations, and to retrieve arguments from the command line using C/C++.

## Part 1

### Over-all Requirements
- [ ] Create a file called **pa1_part1.c**
- [ ] Proper file header
    ```cpp
    /**
     * @file   <NAME OF FILE>
     * @brief  <BRIEF DESCRIPTION ABOUT THE PROGRAM>
     *
     * @author <STUDENT NAME>
     * @date   <DATE STARTED>
     */
    ```
- [ ] Well-chosen variable names
- [ ] Well placed, in-code comments
- [ ] C program MUST take parameters from the command-line

### Program Description
- [ ] Write a program that accepts three command-line arguments:
    * a *sleep time* in milliseconds
    * an *iteration count*
    * a *name*
- [ ] This program should begin by writing:
    ```
    Starting process %pid
    ```
    - [ ] Where `%pid` is replaced with the process id.
- [ ] Then loop *iteration count* number of times printing
    ```
    Howdy %name
    ```
    - [ ] Where `%name` is replaced with the input parameter, 
    - [ ] Each loop should sleep for *sleep time* milliseconds
- [ ] When the last loop is complete it should print:
    ```
    Ending process %pid
    ```
    - [ ] Where `%pid` is replaced with the process id.

### Example Run
For example, if you name is *Bob Crow* with the student number *0123456* the following command should execute the program for 10 iterations, sleeping 4 seconds between iterations:
```
$ pa1_part1 4000 10 Bob
```

The output should look something like:
```
Starting process 28435
Howdy Bob
Howdy Bob
Howdy Bob
Howdy Bob
Howdy Bob
Howdy Bob
Howdy Bob
Howdy Bob
Howdy Bob
Howdy Bob
Ending process 28435
```

## Part 2
- [ ] Copy your code from **Part 1** to a new file, **pa1_part2.c**
- [ ] Remove all references to sleep from this file. Instead, add a `for` loop that does nothing except count to a very large number in the place where you call to sleep was. 
Experiment with this loop so that the timing is similar to the timing in **Part 1**.

## Part 3
- [ ] Answer the questions in Canvas.
