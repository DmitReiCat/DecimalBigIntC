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
    int res = 1;
    while (number > 9) {
        res++;
        number /= 10;
    }
    return res;
}


// deletes extra zeros
void deleteExtraZeroBlocks(bigInt *this) {
    int firstNonZeroBlock = 0;
    while (firstNonZeroBlock < this->size - 1 && *(this->numberPtr + firstNonZeroBlock) == 0) firstNonZeroBlock++;
    for (int blockIndex = 0; blockIndex < firstNonZeroBlock; blockIndex++) {
        *(this->numberPtr + blockIndex) =  *(this->numberPtr + blockIndex + firstNonZeroBlock);
    }
    this->size -= firstNonZeroBlock;
    this->digitCount -= 8 * firstNonZeroBlock;
    this->numberPtr = realloc(this->numberPtr, (this->size) * sizeof(int));
}


// creates and sets new zero block with and an offset of the rest blocks
void insertAndSetZeroBlock(bigInt *this, int number) {
    this->size += 1;
    this->numberPtr = realloc(this->numberPtr, (this->size) * sizeof(int));
    for (int index = this -> size - 1; index > 0; index--) {
        *(this->numberPtr + index) = *(this->numberPtr + index - 1);
    }
    *(this->numberPtr) = number;
    this->digitCount += 8;
}
// inserts number to the beginning of the BigInt       // guaranteed safety for only one digit
void insertToZeroBlock(bigInt *this, int number) {
    if (this->digitCount % 8 != 0) {
        *(this->numberPtr) += number * myPow(10, digitCount(*(this->numberPtr)));
        this->digitCount += 1;
    } else {
        insertAndSetZeroBlock(this, number);
    }
}

void printBigInt(bigInt *this) {
    printf("\n BigInt int= %d[", this->isPositive);
    for (int i = 0; i < this->size; i++) {
        printf("%d,", *(this->numberPtr + i));
    }
    printf("_]\n");
}

bigInt* appendBigIntByDigit(bigInt *this, int digit) {
    if (this->numberPtr == NULL) {
        freeBigInt(this);
        return constructBigIntFromInt(digit);
    } else {
        bigInt *bigInt10 = constructBigIntFromInt(10);
        bigInt *bigDigit = constructBigIntFromInt(digit);
        bigInt *preRes = multiplyBigInts(this, bigInt10, true);
        bigInt *res = plus(preRes, bigDigit, true);
        return res;
    }
};


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


/// Choice of actions on BigInt modules
bigInt* plusMinus(bigInt *firstNumber, bigInt *secondNumber, bool isMinus, bool freeMem) {

    bigInt *longerNumber;
    bigInt *shorterNumber;

    bigInt *result;
    bool sign;
    if (firstNumber->digitCount >= secondNumber->digitCount) {
        sign = firstNumber->isPositive;
        longerNumber = firstNumber;
        shorterNumber = secondNumber;
    } else {
        sign = ((secondNumber->isPositive && !isMinus) || (!secondNumber->isPositive && isMinus));
        longerNumber = secondNumber;
        shorterNumber = firstNumber;
    }

    int operation = 0;
    if (firstNumber->isPositive) operation++;
    if (secondNumber->isPositive) operation++;
    if (isMinus) operation++;
    operation %= 2;
    if (operation == 0) result = moduleSum(longerNumber, shorterNumber, false);
    else result = moduleDiff(longerNumber, shorterNumber, false);

    result->isPositive = sign;
    if (freeMem == true) {
        freeBigInt(longerNumber);
        freeBigInt(shorterNumber);
    }
    return result;
}