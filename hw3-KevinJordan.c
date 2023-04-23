/*************************************************/
/* Welcome to HW3 for CSCI 370 Spring 2022 @ UND
/* Basic math using C with embeded assembly.
/* By Kevin Jordan ID: 1301006 kevin.jordan@und.edu
/* Compile with gcc hw3-KevinJordan.c -o hw3-KevinJordan
/*************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argv, char **argc) {
    int arg1, arg2, add, sub, mul, quo, rem ;
    arg1 = atoi(argc[1]);
    arg2 = atoi(argc[2]);

    printf("Two integer numbers entered: %d %d\n", arg1, arg2);
    //scanf("%d %d", &arg1, &arg2);

    // Perform Addition, Subtraction, Multiplication & Division
    asm( "addl %%ebx, %%eax;" : "=a" (add) : "a" (arg1) , "b" (arg2) );
    asm( "subl %%ebx, %%eax;" : "=a" (sub) : "a" (arg1) , "b" (arg2) );
    asm( "imull %%ebx, %%eax;" : "=a" (mul) : "a" (arg1) , "b" (arg2) );

    // Display results
    printf("%d + %d = %d\n", arg1, arg2, add);
    printf("%d - %d = %d\n", arg1, arg2, sub);
    printf("%d * %d = %d\n", arg1, arg2, mul);

    return 0 ;
}
