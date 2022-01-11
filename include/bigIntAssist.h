#ifndef UNTITLED_BIGINTASSIST_H
#define UNTITLED_BIGINTASSIST_H

#include "newBigInt.h"



int myPow(int x, int n);
int digitCount(int number);
void printBigInt(bigInt *this);
void insertAndSetZeroBlock(bigInt *this, int number);
void insertToZeroBlock(bigInt *this, int number);
void deleteExtraZeroBlocks(bigInt *this);
bigInt* appendBigIntByDigit(bigInt *this, int digit);

int blockSum(int firstBlock, int secondBlock, int *inMem);
int blockSubtraction(int firstBlock, int secondBlock, int *inMem);
bigInt* plusMinus(bigInt *firstNumber, bigInt *secondNumber, bool isMinus, bool freeMem);

#endif //UNTITLED_BIGINTASSIST_H
