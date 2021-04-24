/**
 * @file twoLevelPageTable.c
 * @author Dan Blanchette
 * @brief This program demonstrates two-level page tables.
 * 
 *        Compile:
 *        gcc -Wall twoLevelPageTable.c -o twoLevelPageTable
 * 
 *        Execute:
 *        ./twoLevelPageTable <5 digit hex number>
 * 
 * @date 3/18/2021
 * 
 */
#include <stdio.h>

int rootPageTable[4] = {1, 3, 2, 0};

int userPageTable[4][4] = {
    {
        0xF00D,
        0xCA5E,
        0xCAFE,
        0x0DDB
    },

    {
        0xC0DE,
        0xFACE,
        0xB01D,
        0xBABE
    },

    {
        0xBA5E,
        0x5AFE,
        0xC0CA,
        0xD0C0
    },

    {
        0xDEAD,
        0xBADC,
        0x2DEC,
        0x1AB5
    }
};

// Convert one char that is a valid hex digit into its integer equivielent.
int hex2int(char ch);

int main(int argc, char *argv[]) 
{
    if(argc < 2) 
    {
        printf("Usage: %s <5 digit hex number>\n", argv[0]);
        printf("Ie: \n");
        printf("     %s ACO1A    becomes C0CACO1A\n", argv[0]);
        printf("     %s FAllS    becomes ODDBAllS\n", argv[0]);
        printf("     %s 2FACE    becomes B01DFACE\n", argv[0]);
        printf("     %s 4BEEF    becomes DEADBEEF\n", argv[0]);
        return 1;
    }

    // NOTE: The first hex digit (argv[1][0]) is used to determine 
    // the (outer) root page table index and the (innter) user page table index

    // 1. get the integer equivalent of the hex digit argv[1][0]
    int firstdigit = hex2int(argv[1][0]);
    // 2. determine the root index based on step 1
    int rootIndex = rootPageTable[ firstdigit / 4 ];
    // 3. determine the user index based on step 1
    int userIndex = (firstdigit % 4);
    // 4. print user page table indexed by result in step 2 and 3
    //    followed by value of argv[1] excluding first character
    printf("%04X%s\n", userPageTable[rootIndex][userIndex], &argv[1][1]);
  
    return 0;
}

/**
 * @brief Convert character hex that is a valid hex digit
 *        into its integer equivalent
 * 
 * @param  hex  hexadecimal digit as character  
 * @return int  integer equivalent of hexadecimal character
 */
int hex2int(char ch)
{
    if (ch >= '0' && ch <= '9') 
    {
        return ch - '0';
    }

    if (ch >= 'A' && ch <= 'F') 
    {
        return ch - 'A' + 10;
    }

    if (ch >= 'a' && ch <= 'f') 
    {
        return ch - 'a' + 10;
    }

    return 0;
}
