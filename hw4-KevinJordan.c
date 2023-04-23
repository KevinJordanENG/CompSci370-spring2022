/*************************************************/
/* Welcome to HW4 for CSCI 370 Spring 2022 @ UND
/* C program convering HEX value to Decimal and Binary
/* By Kevin Jordan ID: 1301006 kevin.jordan@und.edu
/* Compile with gcc hw4-KevinJordan.c -o hw4-KevinJordan -lm
/*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

long long HEX2DEC(char hexInput[]) {
    double len = 0;
    long long decimalVal = 0, hexIntArray[100];
    int i, negValFlag = 1;
    len = (double)strlen(hexInput)-1;
    for (i=0; hexInput[i] != '\0'; i++) {
        if (hexInput[0] == '-') {
            negValFlag = -1;
        }
        if ((hexInput[i] >= '0') && (hexInput[i] <= '9')) {
            hexIntArray[i] = hexInput[i] - 48;
        }
        if ((tolower(hexInput[i]) >= 97) && (tolower(hexInput[i]) <= 102)) {
            hexIntArray[i] = tolower(hexInput[i]) - 87;
        }
        decimalVal += hexIntArray[i] * (long long)pow(16, len) * negValFlag;
        len--;
    }
    return decimalVal;
}

int main(void) {
    char hexInput[100];
    long long decimalVal;
    int i, j = 0, binVal[100];
    printf("\n");
    printf("Please enter a HEX value: ");
    scanf("%s", hexInput);
    decimalVal = HEX2DEC(hexInput);
    printf("\n");
    printf("The decimal value is: %lld\n", decimalVal);
    printf("\n");
    printf("The binary value is: ");
    if (decimalVal == 0) printf("0");
    if (decimalVal < 0) {
        printf("-");
        decimalVal = decimalVal * -1;
    }
    for (i=0; decimalVal > 0; i++) {
        binVal[i] = (decimalVal % 2);
        decimalVal /= 2;
        j++;
    }
    j--;
    for (i=j; i>=0; i--) {
        printf("%d", binVal[i]);
    }
    printf("\n\n");
    return 0;
}
