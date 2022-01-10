#ifndef UNTITLED_BIGINTASSIST_H
#define UNTITLED_BIGINTASSIST_H

#include "newBigInt.h"

int myPow(int x, int n);
int digitCount(int number);
void printBigInt(bigigInt *this);
void insertAndSetZeroBlock(bigigInt *this, int number);
void insertToZeroBlock(bigigInt *this, int number);
void freeBigInt(bigigInt *this);
void deleteExtraZeroBlocks(bigigInt *this);
void appendBigIntByDigit(bigigInt *this, int digit);

int blockSum(int firstBlock, int secondBlock, int *inMem);
int blockSubtraction(int firstBlock, int secondBlock, int *inMem);
bigigInt* plusMinus(bigigInt *firstNumber, bigigInt *secondNumber, bool freeMem);

#endif //UNTITLED_BIGINTASSIST_H
