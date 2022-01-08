#include "../include/newBigInt.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#include "../include/bigIntAssist.h"


newBigInt* constructBigInt(char str[]) {
    newBigInt *bigIntRes = NULL;
    bigIntRes = (newBigInt*) malloc(sizeof(newBigInt));

    int strSize = (int)strlen(str);
    bigIntRes->size = (strSize - 1) / 8;
    if ((strSize - 1) % 8 != 0) bigIntRes->size += 1;
    bigIntRes->digitCount = strSize - 1;

    int startIndex = 1;
    if (str[0] == '-') {
        bigIntRes->isPositive = false;
    } else if (str[0] == '+') {
        bigIntRes->isPositive = true;
    } else {
        bigIntRes->isPositive = true;
        bigIntRes->size = strSize / 8;
        if (strSize % 8 != 0) bigIntRes->size += 1;
        bigIntRes->digitCount = (int)strlen(str);
        startIndex = 0;
    }
    bigIntRes->numberPtr = (int*)calloc(bigIntRes->size, sizeof(int));

    int arrIndex = 0;
    int digitsToAdd = bigIntRes->digitCount % 8;
    if (digitsToAdd == 0) digitsToAdd = 8;
    for (int i = startIndex; i < (int)strlen(str); i++) {
        int digit = str[i] - '0';
        *(bigIntRes->numberPtr + arrIndex) *= 10;
        *(bigIntRes->numberPtr + arrIndex) += digit;
        digitsToAdd--;
        if (digitsToAdd == 0) {
            digitsToAdd = 8;
            arrIndex++;
        }
    }

    return bigIntRes;
}

char* toString(newBigInt *this ) {
    char *result;
    int i = 1;
    result = (char*)malloc(sizeof(char));

    if (this -> isPositive) result[0] = '+';
    else result[0] = '-';

    int digitsToAdd = this->digitCount % 8;
    if (digitsToAdd == 0) digitsToAdd = 8;
    for (int blockIndex = 0; blockIndex < this->size; blockIndex++) {
        int number = *(this->numberPtr + blockIndex);
        for (int indexInBlock = 0; digitsToAdd > 0; indexInBlock++) {
            char digit = (number % myPow(10, digitsToAdd) / myPow(10, digitsToAdd - 1)) + '0';

            result = (char*) realloc(result, (i + 1) * sizeof(char));
            result[i] = digit;
            i++;
            digitsToAdd--;
        }
        digitsToAdd = 8;
    }

//    if (this -> isPositive) result[0] = '+';
//    else result[0] = '-';
//    for (int index = this -> size - 1; index > - 1; index--) {
//        result = (char*) realloc(result, (i + 1) * sizeof(char));
//        result[i] = *(this->numberPtr + index) + '0';
//        i++;
//    }
    result = (char*) realloc(result, (i + 1) * sizeof(char));
    result[i] = '\0';

    return result;
}
