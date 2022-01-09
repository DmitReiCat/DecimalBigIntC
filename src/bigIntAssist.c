#include <stdio.h>
#include <stdlib.h>
#include "../include/bigIntAssist.h"

int myPow(int x,int n) {
    int i;
    int number = 1;
    for (i = 0; i < n; ++i)
        number *= x;

    return(number);
}

int digitCount(int number) {
    int result = 1;
    while (number > 9) {
        result++;
        number /= 10;
    }
    return result;
}

/// sum inside of one block with overflow in inMem
int blockSum(int firstBlock, int secondBlock, int *inMem) {
    int tempSum = firstBlock + secondBlock + *inMem;
    if (tempSum >= 100000000) {
        *inMem = 1;
        return tempSum - 100000000;
    } else {
        *inMem = 0;
        return tempSum;
    }
}


/// creates and sets new zero block with and an offset of the rest blocks
void insertAndSetZeroBlock(newBigInt *this, int number) {
    this -> size += 1;
    this -> numberPtr = realloc(this -> numberPtr, (this -> size) * sizeof(int));
    for (int index = this -> size - 1; index > 0; index--) {
        *(this -> numberPtr + index) = *(this -> numberPtr + index - 1);
    }
    *(this -> numberPtr) = number;
}

/// inserts number to the beginning of the BigInt       // guaranteed safety for only one digit
void insertToZeroBlock(newBigInt *this, int number) {
    if (this->digitCount % 8 != 0) {
        *(this->numberPtr) += number * myPow(10, digitCount(*(this->numberPtr)));
    } else {
        insertAndSetZeroBlock(this, number);
    }
}


void printBigInt(newBigInt *this) {
    printf("BigInt= [");
    for (int i = 0; i < this->size; i++) {
        printf("%d,", *(this->numberPtr + i));
    }
    printf("_]\n");
};
