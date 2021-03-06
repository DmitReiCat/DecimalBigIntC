#include <stdio.h>
#include <stdlib.h>
#include <vcruntime_string.h>
#include "../include/bigIntAssist.h"
#include "../include/consts.h"

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
    while (firstNonZeroBlock < this->size - 1 && this->numberPtr[firstNonZeroBlock] == 0) firstNonZeroBlock++;
    this->size -= firstNonZeroBlock;
    memmove(this->numberPtr, this->numberPtr + firstNonZeroBlock, (this->size) * sizeof(int));
    this->digitCount -= DIGITS_IN_BLOCK * firstNonZeroBlock;
    this->numberPtr = realloc(this->numberPtr, this->size * sizeof(int));
}


// creates and sets new zero block with and an offset of the rest blocks
void insertAndSetZeroBlock(bigInt *this, int number) {
    this->size += 1;
    this->numberPtr = realloc(this->numberPtr, this->size * sizeof(int));
    memmove(this->numberPtr + 1, this->numberPtr, (this->size - 1) * sizeof(int));
    this->numberPtr[0] = number;
    this->digitCount += DIGITS_IN_BLOCK;
}
// inserts number to the beginning of the BigInt       // guaranteed safety for only one digit
void insertToZeroBlock(bigInt *this, int number) {
    if (this->digitCount % DIGITS_IN_BLOCK != 0) {
        this->numberPtr[0] += number * myPow(10, digitCount(this->numberPtr[0]));
        this->digitCount += 1;
    } else {
        insertAndSetZeroBlock(this, number);
    }
}

void printBigInt(bigInt *this) {
    printf("\n BigInt int= %d[", this->isPositive);
    for (int i = 0; i < this->size; i++) {
        printf("%d,", this->numberPtr[i]);
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

        bigInt *preRes = multiplyBigInts(this, bigInt10);
        freeBigInt(this);
        freeBigInt(bigInt10);

        bigInt *res = plus(preRes, bigDigit);
        freeBigInt(preRes);
        freeBigInt(bigDigit);
        return res;
    }
};


/// sum inside of one block with overflow in inMem
int blockSum(int firstBlock, int secondBlock, int *inMem) {
    int tempSum = firstBlock + secondBlock + *inMem;
    if (tempSum >= WORD_LENGTH) {
        *inMem = 1;
        return tempSum - WORD_LENGTH;
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
        return tempDiff + WORD_LENGTH;
    } else {
        *inMem = 0;
        return tempDiff;
    }
}


/// Choice of actions on BigInt modules
bigInt* plusMinus(bigInt *firstNumber, bigInt *secondNumber, bool isMinus) {
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
    if (operation == 0) result = moduleUnited(longerNumber, shorterNumber, true);
    else result = moduleUnited(longerNumber, shorterNumber, false);

    result->isPositive = sign;
    return result;
}