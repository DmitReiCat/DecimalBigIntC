#ifndef UNTITLED_NEWBIGINT_H
#define UNTITLED_NEWBIGINT_H

#include <stdbool.h>
#include "list.h"

typedef struct BigInteger {
    bool isPositive;
    int size;
    int digitCount;
    int *numberPtr;
} newBigInt;

newBigInt* constructBigIntFromInt(int integer);
newBigInt* constructBigIntFromStr(char string[]);
newBigInt* constructBigIntFromReversedList(listOfInt *list);
char* bigIntToString(newBigInt *this);
int bigIntToInt(newBigInt *this);

newBigInt* moduleSum(newBigInt *firstNumber, newBigInt *secondNumber, bool freeMem);
newBigInt* moduleDiff(newBigInt *firstNumber, newBigInt *secondNumber, bool freeMem);
newBigInt* plus(newBigInt *firstNumber, newBigInt *secondNumber, bool freeMem);
newBigInt* minus(newBigInt *firstNumber, newBigInt *secondNumber, bool freeMem);
newBigInt *multiplyBigInts(newBigInt *firstNumber, newBigInt *secondNumber);


#endif //UNTITLED_NEWBIGINT_H
