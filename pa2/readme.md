PA2: Shells Part I
Purpose: To recall the use of fork() and execvp().

Introduction
In this assignment you will implement a simple shell program similar to the Unix shell bash or the command prompt in Windows. You will call your gdshell (where gd should be replaced with your initials).

The shell will support execution of programs in UNIX. You must implement your solution in C.

Be sure to study the man pages for the various functions suggested in this assignment.

The functions are in section 2 of the man pages, so you should type (as an example):

$ man 2 waitpid
Requirements
 Use three file structure
Make your program modular. Break the program into functions.
Each file should have a file header comment
Each function should have a function header comment
 A brief description of what the function does
 A description of each parameter
 A description of what the function returns
 Create a Makefile to build and maintain the program.
 Commit your code frequently and provide descriptive commit messages.
 Refactor code that uses efficient approaches.
 Write in-line comments in your code for readability.
Part 1: Basic execution
 Using fgets() create a shell that prompts the user with the prompt gdshell> continually until the user enters the command exit.

 When the shell first starts to display the message:

Created By: <Your Name>
Type "help" to see implemented commands

gdshell>
 This shell should ignore all commands except exit, which ends the program.
Here is a sample session of how your shell should look:

$ ./gdshell
Created By: Gabe de la Cruz
Type "help" to see implemented commands

gdshell> help
gdshell> ls -l
gdshell> exit
$
 Test and make sure program is working correctly. Commit and push code to GitHub.
Part 2: Help
 If the user types:
gdshell> help
Display the message:
pwd  - Print the current working directory
exit - Exit Shell
help - Display this message

bglist        - List background programs
bgkill <int>  - Kill background process <int> int values: 1-5
<UNIX cmd>    - Spawn child process, execute <UNIX cmd> in the foreground
bg <UNIX cmd> - Spawn child process, execute <UNIX cmd> in the backgroud
Here is a sample session:

$ ./gdshell
Created By: Gabe de la Cruz
Type "help" to see implemented commands

gdshell> help
pwd  - Print the current working directory
exit - Exit Shell
help - Display this message

bglist        - List background programs
bgkill <int>  - Kill background process <int> int values: 1-5
<UNIX cmd>    - Spawn child process, execute <UNIX cmd> in the foreground
bg <UNIX cmd> - Spawn child process, execute <UNIX cmd> in the background

gdshell> exit
$
 Test and make sure program is working correctly. Commit and push code to GitHub.
NOTE: Although the help screen lists bglist, bgkill and bg, you do not have to implement them for this assignment. Just list them in the help screen.

For this assignment all you need to implement is exit (Part 1), help (Part 2), and foreground UNIX commands (Part 3).

Part 3: fork() and execvp()
 Using fork() and execvp(), implement the ability for the user to execute arbitrary commands using your shell.

 If the user types:

gdshell> ls -l /usr
Your shell should execute the ls command with the parameters -l and /usr, which should result in the contents of the directory /usr being displayed on the screen.

 In CS270, you should be familiar that excecvp, requires an array of C-string as one of its parameters. You will have to convert the C-string ls -l /usr into an array of strings with the last element assigned with NULL.

// Example of the use of execvp, but your approach should work for any command and should be dynamic
char *args[4];
args[0] = "ls";
args[1] = "-l";
args[2] = "/usr";
args[3] = NULL;
execvp(args[0], args);
There is many approaches in breaking the C-strings into individual strings. Your approach to this problem will be graded heavily. In a file part3.txt, you have to defend your approach.

 Explain first what your algorithm is in breaking the string into an array of strings. Be technical with your explanation (e.g. whether you use dynamic array or static array, etc.)
 What are the limitations of your approach if there are any? (e.g. Can it accept commands with leading, in between, and trailing white spaces and still break the strings correctly, etc.)
 Why makes your approach efficient and are there parts of it that are inefficient?
Here is a sample session of how your shell should look:

$ ./gdshell
Created By: Gabe de la Cruz
Type "help" to see implemented commands

gdshell> help
pwd  - Print the current working directory
exit - Exit Shell
help - Display this message

bglist        - List background programs
bgkill <int>  - Kill background process <int> int values: 1-5
<UNIX cmd>    - Spawn child process, execute <UNIX cmd> in the foreground
bg <UNIX cmd> - Spawn child process, execute <UNIX cmd> in the background

gdshell> ls -l /usr
total 5
drwxr-xr-x   2 root root 69632 Apr  4 05:44 bin
drwxr-xr-x   4 root root  4096 Jun 23 10:48 doc
drwxr-xr-x   2 root root  4096 Mar 14 01:13 etc
drwxr-xr-x   2 root root  4096 Mar 14 08:32 games
drwxr-xr-x 123 root root 16384 Mar 19 04:18 include
gdshell> exit
$
 Test and make sure program is working correctly. Commit and push code to GitHub.
 Submit GitHub URL in Canvas.