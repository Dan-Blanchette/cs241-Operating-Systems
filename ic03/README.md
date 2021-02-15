# IC03 - Linux/UNIX Primer & `pthread`

## count.c
### Purpose
Illustrate basic use of `pthread` and the issue of using unprotected shared variables: create some threads, each of which prints a message, then counts to 10,000.
### Input/Output
The input to the **count** program is the number of threads to create and the output is a message from each thread and the final total.
### Compile
Since **count.c** uses the `pthread.h` C library, we need to tell the compiler to link to this particular library. Thus, the command-line option `-lpthread` must be added towards the end of the command below or you will get an error during compilation.
```
$ gcc -g -Wall count.c -o count -lpthread
```
### Usage
Replace the command-line argument `<thread_count>` with a number. This number represents how many threads will be created in the **count** program.
```
$ ./count <thread_count>
```

## hello.c
- [ ] Write a C program **hello.c** that takes a *number* and a *name*. The program prints out **Hello *\<name\>*** repeatedby based on the *number*.
  ```
  $ ./hello 3 cs241
  Hello cs241
  Hello cs241
  Hello cs241
  ```

- [ ] Be sure to put a proper file header comment.
  ```cpp
  /**
   * @file   <name_of_file>
   * @author <student_name>
   * @brief  <brief_description_of_what_the_program_does>
   * @date   <date_started>
   * 
   */
  ```

- [ ] Also, include a `usage()` function if the user gives incorrect parameters. Look inside **count.c** for some guidance on what `usage()` should look like and how it should be incorporated into the program.

- [ ] Ensure it compiles cleanly with:
  ```
  $ gcc -Wall hello.c -o hello
  ```

- [ ] Submit it as part of this repo
  ```
  $ git add hello.c
  $ git commit -m "hello program completed and has been tested with no issues"
  $ git push
  ```
  
- [ ] After successfully pushing your code to Github. Verify here that the code is in Github, then in Canvas, select **true** on the last IC03 question.
