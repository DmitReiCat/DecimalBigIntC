#ifndef UNTITLED_NEWBIGINT_H
#define UNTITLED_NEWBIGINT_H

#include <stdbool.h>

typedef struct BigInteger {
    bool isPositive;
    int size;
    int digitCount;
    int *numberPtr;
} newBigInt;

newBigInt* constructBigInt(char str[]);
char* toString(newBigInt *this);


#endif //UNTITLED_NEWBIGINT_H
