//
// Created by t3col on 29-Dec-21.
//

#ifndef UNTITLED_BIGINT_H
#define UNTITLED_BIGINT_H
#include "stdbool.h"
typedef struct BigInteger {
    bool isPositive;
    int size;
    int *numberPtr;
} bigInt;


bigInt *constructBigInt(char str[]);
void printBigInt(bigInt *number);
void printStats(bigInt *number);
bigInt *minus(bigInt *firstNumber, bigInt *secondNumber);
bigInt *plus(bigInt *firstNumber, bigInt *secondNumber);
bigInt *multiply(bigInt *firstNumber, bigInt *secondNumber);
bigInt *myDiv(bigInt *numerator, bigInt *denominator);
bigInt *modResult(bigInt *numerator, bigInt *denominator);
int *toBigString(bigInt *this );
int compareTo(bigInt *this, bigInt *other);
bigInt *add(bigInt *firstNumber, bigInt *secondNumber);

#endif //UNTITLED_BIGINT_H
