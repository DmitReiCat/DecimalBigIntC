#ifndef UNTITLED_NEWBIGINT_H
#define UNTITLED_NEWBIGINT_H

#include <stdbool.h>
#include "list.h"

typedef struct BigInteger {
    bool isPositive;
    int size;
    int digitCount;
    int *numberPtr;
} bigInt;

bigInt* constructBigIntFromInt(int integer);
bigInt* constructBigIntFromStr(char string[]);
bigInt* constructBigIntFromList(listOfInt *list, bool freeMem);
char* bigIntToString(bigInt *this);
int bigIntToInt(bigInt *this);
void freeBigInt(bigInt *this);

bigInt* moduleUnited(bigInt *firstNumber, bigInt *secondNumber, bool isSum, bool freeMem);
bigInt* plus(bigInt *firstNumber, bigInt *secondNumber, bool freeMem);
bigInt* minus(bigInt *firstNumber, bigInt *secondNumber, bool freeMem);
bigInt *multiplyBigInts(bigInt *firstNumber, bigInt *secondNumber, bool freeMem);
bigInt *divisionProcess(bigInt *nominator, bigInt *denominator, bool onlyRemains, bool freeMem);
bigInt *bigIntDiv(bigInt *numerator, bigInt *denominator, bool freeMem);
bigInt *bigIntMod(bigInt *numerator, bigInt *denominator, bool freeMem);
int compareTo(bigInt *this, bigInt *other, bool onlyModules);


#endif //UNTITLED_NEWBIGINT_H
