#ifndef UNTITLED_NEWBIGINT_H
#define UNTITLED_NEWBIGINT_H

#include <stdbool.h>
#include "list.h"

typedef struct BigInteger {
    bool isPositive;
    int size;
    int digitCount;
    int *numberPtr;
} bigigInt;

bigigInt* constructBigIntFromInt(int integer);
bigigInt* constructBigIntFromStr(char string[]);
bigigInt* constructBigIntFromReversedList(listOfInt *list);
bigigInt* constructBigIntFromList(listOfInt *list);
char* bigIntToString(bigigInt *this);
int bigIntToInt(bigigInt *this);

bigigInt* moduleSum(bigigInt *firstNumber, bigigInt *secondNumber, bool freeMem);
bigigInt* moduleDiff(bigigInt *firstNumber, bigigInt *secondNumber, bool freeMem);
bigigInt* plus(bigigInt *firstNumber, bigigInt *secondNumber, bool freeMem);
bigigInt* minus(bigigInt *firstNumber, bigigInt *secondNumber, bool freeMem);
bigigInt *multiplyBigInts(bigigInt *firstNumber, bigigInt *secondNumber, bool freeMem);
bigigInt *divisionProcess(bigigInt *nomerator, bigigInt *denominator, bool onlyRemains);
int compareTo(bigigInt *this, bigigInt *other);


#endif //UNTITLED_NEWBIGINT_H
