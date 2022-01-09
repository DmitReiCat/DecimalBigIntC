#include "../include/newBigInt.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#include "../include/bigIntAssist.h"


/// constructs bigInt from int
newBigInt* constructBigIntFromInt(int integer) {
    newBigInt *bigIntRes = NULL;
    bigIntRes = (newBigInt*) malloc(sizeof(newBigInt));

    int digitsCounted = digitCount(integer);
    bigIntRes->size = digitsCounted / 8;
    if (digitsCounted % 8 != 0) bigIntRes->size++;
    bigIntRes->digitCount = digitsCounted;

    if (integer >= 0) {
        bigIntRes->isPositive = true;
    } else {
        bigIntRes->isPositive = false;
    }

    bigIntRes->numberPtr = (int*)calloc(bigIntRes->size, sizeof(int));

    int arrIndex = 0;
    int digitsToAdd = bigIntRes->digitCount % 8;
    if (digitsToAdd == 0) digitsToAdd = 8;

    for (int i = 0; i < digitsCounted; i++) {
        int digit = (integer % myPow(10, digitsCounted - i) / myPow(10, digitsCounted - i - 1));
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



/// constructs bigInt from string
newBigInt* constructBigIntFromStr(char string[]) {
    newBigInt *bigIntRes = NULL;
    bigIntRes = (newBigInt*) malloc(sizeof(newBigInt));

    int strSize = (int)strlen(string);
    bigIntRes->size = (strSize - 1) / 8;
    if ((strSize - 1) % 8 != 0) bigIntRes->size += 1;
    bigIntRes->digitCount = strSize - 1;

    int startIndex = 1;
    if (string[0] == '-') {
        bigIntRes->isPositive = false;
    } else if (string[0] == '+') {
        bigIntRes->isPositive = true;
    } else {
        bigIntRes->isPositive = true;
        bigIntRes->size = strSize / 8;
        if (strSize % 8 != 0) bigIntRes->size += 1;
        bigIntRes->digitCount = (int)strlen(string);
        startIndex = 0;
    }
    bigIntRes->numberPtr = (int*)calloc(bigIntRes->size, sizeof(int));

    int arrIndex = 0;
    int digitsToAdd = bigIntRes->digitCount % 8;
    if (digitsToAdd == 0) digitsToAdd = 8;
    for (int i = startIndex; i < (int)strlen(string); i++) {
        int digit = string[i] - '0';
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






/// Sum of numbers' modules
newBigInt *moduleAdd(newBigInt *firstNumber, newBigInt *secondNumber) {
    newBigInt *bigIntRes = NULL;
    bigIntRes = (newBigInt*) malloc(sizeof(newBigInt));
    int inMem = 0;

    bigIntRes->size = firstNumber->size ;
    bigIntRes->isPositive = firstNumber->isPositive ;
    bigIntRes->numberPtr = (int*) malloc((bigIntRes -> size) * sizeof(int));
    int blockDiff = firstNumber->size - secondNumber->size;

    for (int blockIndex = secondNumber->size - 1; blockIndex >= 0; blockIndex--) {
        int firstBlock = *(firstNumber->numberPtr + (blockDiff + blockIndex));
        int secondBlock = *(secondNumber->numberPtr + blockIndex);
        *(bigIntRes->numberPtr + (blockDiff + blockIndex)) = blockSum(firstBlock, secondBlock, &inMem);
    }
    for (int blockIndex = blockDiff - 1; blockIndex >= 0; blockIndex--) {
        int block = *(firstNumber->numberPtr + blockIndex);
        *(bigIntRes->numberPtr + blockIndex) = blockSum(block, 0, &inMem);
    }
    bigIntRes->digitCount = firstNumber->digitCount;
    if (inMem != 0) {
        insertToZeroBlock(bigIntRes, inMem);
        bigIntRes->digitCount += 1;
    }
    return bigIntRes;
}

/// converts bigint to string
char* bigIntToString(newBigInt *this) {
    char *result;
    int i = 1;
    result = (char*)malloc(sizeof(char));

    if (this->isPositive) result[0] = '+';
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
    result = (char*) realloc(result, (i + 1) * sizeof(char));
    result[i] = '\0';

    return result;
}

/// converts bigint to string
int bigIntToInt(newBigInt *this) {
    //TODO comparing for safe conversion
    int result = 0;

    int digitsToAdd = this->digitCount % 8;
    if (digitsToAdd == 0) digitsToAdd = 8;
    for (int blockIndex = 0; blockIndex < this->size; blockIndex++) {
        int number = *(this->numberPtr + blockIndex);
        for (int indexInBlock = 0; digitsToAdd > 0; indexInBlock++) {
            int digit = number % myPow(10, digitsToAdd) / myPow(10, digitsToAdd - 1);
            result *= 10;
            result += digit;
            digitsToAdd--;
        }
        digitsToAdd = 8;
    }

    if (!this->isPositive) result *= -1;
    return result;
}

/// frees memory taken by bigInt
void freeBigInt(newBigInt *this) {
    free(this->numberPtr);
    free(this);
}