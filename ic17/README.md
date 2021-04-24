# IC17 - Two-level Page Table

### Purpose
This exercise will help you understand two-level page table.

### Pre-Task
- [ ] Open **twoLevelPageTable.c**
- [ ] Update file header comment with your information and today's date
- [ ] There two global arrays `rootPageTable` and `userPageTable`
    * `rootPageTable` simulates the root page table (outer page table) in the two-level page  table
    * `userPageTable` simulates the user page table (inner page table) in the two-level page  table
- [ ] The `hex2int()` function if provided a hex digit (as character type) simply returns the integer equivalent
- [ ] After completing the task below, compile your code using the command below
    ```
    $ gcc -Wall twoLevelPageTable.c -o twoLevelPageTable
    ```

### Your Task
- [ ] In the `main()` function, update the code so that it does a two-level page look-up on any inputs. Observe the example input and program output below. Then identify how the input is used to get the following output.
    ```
    $ ./twoLevelPageTable AC01A
    C0CAC01A
    $ ./twoLevelPageTable FAllS
    ODDBAllS
    $ ./twoLevelPageTable 2FACE
    B01DFACE
    $ ./twoLevelPageTable 4BEEF
    DEADBEAF
    ```
- [ ] Once your code succesffully works with the sample input above, answer the questions in Canvas
- [ ] Commit and push your code to Github. Verify here that the code is in Github, then submit GitHub URL in Canvas.
