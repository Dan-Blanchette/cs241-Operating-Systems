# IC07 - Create a Dispatcher Program

## scheduler.c
### Purpose
This exercise will reinforce scheduling by having you create a dispatcher program 

### Compile
Since **scheduler.c** 
```
$ gcc -Wall scheduler.c -o scheduler
```
### Usage
This program already parses the command line inputs and sets up a 2D array of instructions
```
$ ./scheduler 5 3 10 10 5 7 3
```
* `5` - indicates there are 5 processes
* `3` - is the quantum
  * That is the number of instructions that each process will execute before giving control back to the dispatcher.
* The other inputs `10`, `10`, `5`, `7` and `3`, are the lengths of the processes

### Current Program Output 
The program currently gives the following output:

|  `A`   |  `B`   |  `C`   |  `D`   |  `E`   |
|--------|--------|--------|--------|--------|
| `1000` | `2000` | `3000` | `4000` | `5000` |
| `1004` | `2004` | `3004` | `4004` | `5004` |
| `1008` | `2008` | `3008` | `4008` | `5008` |
| `100C` | `200C` | `300C` | `400C` | `0000` |
| `1010` | `2010` | `3010` | `4010` | `0000` |
| `1014` | `2014` | `0000` | `4014` | `0000` |
| `1018` | `2018` | `0000` | `4018` | `0000` |
| `101C` | `201C` | `0000` | `0000` | `0000` |
| `1020` | `2020` | `0000` | `0000` | `0000` |
| `1024` | `2024` | `0000` | `0000` | `0000` |

Notice that **Process E** only has 3 instructions so when you do your trace it will only get one quantum.

### Mission
Your mission is to write the trace function that will simply print out the order in which instructions will be executed. 

Write the code for the function below in **scheduler.c**

```cpp
void dispatchPrograms(int numberOfPrograms, int quantum, int programs[MAXPROGS][MAXINSTRUCTIONS])
{
    // Your code here
}
```

For the above inputs, your program output should start like this:
```
1000

1004

1008

0100 - Dispatcher

2000

etc.
```

- [ ] Ensure it compiles cleanly with:
  ```
  $ gcc -Wall scheduler.c -o scheduler
  ```
- [ ] Try the **scheduler** program with different combinations of inputs

- [ ] Demo the program to the instructor when you are done

- [ ] Add-Commit-Push code to Github
  ```
  $ git add hello.c
  $ git commit -m "hello program completed and has been tested with no issues"
  $ git push
  ```
  
- [ ] After successfully pushing your code to Github. Verify here that the code is in Github

- [ ] Submit this repo's URL by copying it from the browser's address bar and paste it in the IC07b Canvas submission page.
