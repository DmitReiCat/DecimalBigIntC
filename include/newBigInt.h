#ifndef UNTITLED_NEWBIGINT_H
#define UNTITLED_NEWBIGINT_H

#include <stdbool.h>

typedef struct BigInteger {
    bool isPositive;
    int size;
    int digitCount;
    int *numberPtr;
} newBigInt;
newBigInt* constructBigIntFromInt(int integer);
newBigInt* constructBigIntFromStr(char string[]);
char* bigIntToString(newBigInt *this);
int bigIntToInt(newBigInt *this);
newBigInt *moduleAdd(newBigInt *firstNumber, newBigInt *secondNumber);


#endif //UNTITLED_NEWBIGINT_H
