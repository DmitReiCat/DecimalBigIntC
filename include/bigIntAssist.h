#ifndef UNTITLED_BIGINTASSIST_H
#define UNTITLED_BIGINTASSIST_H

#include "newBigInt.h"

int myPow(int x, int n);
int digitCount(int number);
void printBigInt(newBigInt *this);
void insertAndSetZeroBlock(newBigInt *this, int number);
void insertToZeroBlock(newBigInt *this, int number);
void freeBigInt(newBigInt *this);
void deleteExtraZeroBlocks(newBigInt *this);
void appendEmptyBlock(newBigInt *this);
void appendBlock(newBigInt *this, int number);
void reverse(newBigInt *this);

int blockSum(int firstBlock, int secondBlock, int *inMem);
int blockSubtraction(int firstBlock, int secondBlock, int *inMem);
newBigInt* plusMinus(newBigInt *firstNumber, newBigInt *secondNumber, bool freeMem);
int blockMultiplication(int firstBlock, int secondBlock, int *inMem);

#endif //UNTITLED_BIGINTASSIST_H
