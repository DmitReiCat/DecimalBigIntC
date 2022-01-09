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


///Difference if two blocks with underflow in inMem
int blockSubtraction(int firstBlock, int secondBlock, int *inMem) {
    int tempDiff = firstBlock - secondBlock - *inMem;
    if (tempDiff < 0) {
        *inMem = 1;
        return tempDiff + 100000000;
    } else {
        *inMem = 0;
        return tempDiff;
    }
}


/// deletes extra zeros without changing digitCount
void deleteExtraZeroBlocks(newBigInt *this) {
    int firstNonZeroBlock = 0;
    while (firstNonZeroBlock < this->size - 1 && *(this->numberPtr + firstNonZeroBlock) == 0) firstNonZeroBlock++;
    for (int blockIndex = 0; blockIndex < firstNonZeroBlock; blockIndex++) {
        *(this->numberPtr + blockIndex) =  *(this->numberPtr + blockIndex + firstNonZeroBlock);
    }
    this->size -= firstNonZeroBlock;
    this->digitCount -= 8 * firstNonZeroBlock;
    this->numberPtr = realloc(this->numberPtr, (this->size) * sizeof(int));
}

/// deletes extra zeros and changes digitCount
//void deleteExtraZeroBlocks(newBigInt *this, newBigInt *reference) {
//    int blocksToCount = deleteExtraZeroBlocks(this);
//    int digitsCounted = 0;
//    for (int blockIndex = 0; blockIndex < blocksToCount; blockIndex++) {
//        digitsCounted += digitCount(*(reference->numberPtr + blockIndex));
//    }
//    this->digitCount -= digitsCounted;
//}


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
