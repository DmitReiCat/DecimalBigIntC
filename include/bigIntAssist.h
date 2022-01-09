#ifndef UNTITLED_BIGINTASSIST_H
#define UNTITLED_BIGINTASSIST_H

#include "newBigInt.h"

int myPow(int x, int n);
int blockSum(int firstBlock, int secondBlock, int *inMem);
void printBigInt(newBigInt *this);
void insertAndSetZeroBlock(newBigInt *this, int number);
void insertToZeroBlock(newBigInt *this, int number);
int digitCount(int number);
void freeBigInt(newBigInt *this);

#endif //UNTITLED_BIGINTASSIST_H
