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
bigInt* constructEmptyBigInt();
bigInt* constructBigIntFromInt(int integer);
bigInt* constructBigIntFromStr(char string[]);
bigInt* constructBigIntFromList(listOfInt *list);
char* bigIntToString(bigInt *this);
int bigIntToInt(bigInt *this);
void freeBigInt(bigInt *this);

bigInt* moduleUnited(bigInt *firstNumber, bigInt *secondNumber, bool isSum);
bigInt* plus(bigInt *firstNumber, bigInt *secondNumber);
bigInt* minus(bigInt *firstNumber, bigInt *secondNumber);

bigInt *multiplyBigInts(bigInt *firstNumber, bigInt *secondNumber);
bigInt *divisionProcess(bigInt *nominator, bigInt *denominator, bool onlyRemains);
bigInt *bigIntDiv(bigInt *numerator, bigInt *denominator);
bigInt *bigIntMod(bigInt *numerator, bigInt *denominator);
int compareTo(bigInt *this, bigInt *other, bool onlyModules);


#endif //UNTITLED_NEWBIGINT_H
