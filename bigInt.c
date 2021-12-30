//
// Created by t3col on 29-Dec-21.
//
#include "bigInt.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"

// вспомогательной вывод формы bigInt в памяти
void printBigInt(bigInt *this) {
    if (this -> isPositive) printf("+");
    else printf("-");
    for (int i = this -> size - 1; i > -1; i--) {
        printf("%d", *(this -> numberPtr + i));
    }
    printf("\n");
}

// вспомогательной вывод адресов и значений у bigInt
void printStats(bigInt *number) {
    printf("Adresses\n");
    printf("ptr= %p size= %p isPositive= %p\n",
           number->numberPtr,
           &number->size,
           &number->isPositive
    );
    printf("Values\n");
    printf("ptr= %p size= %d isPositive= %d\n",
           number->numberPtr,
           number->size,
           number->isPositive
    );
    printf("Number\n");
    printf("sign = %d\n", number -> isPositive);
    printBigInt(number);
    printf("\n");
}

void appendString(int *string, char item) {
    string = realloc(string, (strlen(string) + 1) * sizeof(int));
    *(string + strlen(string)) = item;
}

void append(bigInt *this, int item) {
    this -> size += 1;
    this -> numberPtr = realloc(this -> numberPtr, (this -> size) * sizeof(int));
    *(this -> numberPtr + this -> size - 1 ) = item;
}

void removeLast(bigInt *this) {
    this -> size -= 1;
    this -> numberPtr = realloc(this -> numberPtr, (this -> size) * sizeof(int));
}

void clear(bigInt *this) {
    this->size = 0;
    this->isPositive = true;
    free(this->numberPtr);
    this -> numberPtr = (int*) malloc(0 * sizeof(int));
}

void insertFirstNumber(bigInt *this, int number) {
    this -> size += 1;
    this -> numberPtr = realloc(this -> numberPtr, (this -> size) * sizeof(int));

    for (int index = this -> size - 1; index > 0; index--) {
        *(this -> numberPtr + index) = *(this -> numberPtr + index - 1);
    }
    *(this -> numberPtr) = number;
}

void reverse(bigInt *this) {
    int currentElement = *(this -> numberPtr);
    int tmpElement;
    for (int index = 0; index < this -> size - 1; index++) {
        tmpElement = *(this -> numberPtr + 1);
        *(this -> numberPtr + 1) = currentElement;
        currentElement = tmpElement;
    }
    *(this -> numberPtr) = currentElement;
}


/// Создание bigInt
bigInt *constructBigInt(char str[]) {
    bigInt *bigIntRes = NULL;
    bigIntRes = (bigInt*) malloc(sizeof(bigInt));
    bigIntRes -> size = (int) strlen(str) - 1;
    bigIntRes -> numberPtr = (int*) malloc((bigIntRes -> size) * sizeof(int));
    int startIndex = 1;
    if (str[0] == '-') {
        bigIntRes -> isPositive = false;
    } else if (str[0] == '+') {
        bigIntRes -> isPositive = true;
    } else {
        startIndex = 0;
    }

    for (int i = startIndex; i < strlen(str); i++) {
        *(bigIntRes -> numberPtr + i - 1) = str[strlen(str) - i] - '0';
    }

    return bigIntRes;
}


int compareTo(bigInt *this, bigInt *other) {
    if (this -> size > other -> size) return 1;
    else if (this -> size < other -> size) return -1;
    else {
        for (int index = this -> size; index > 0; index--) {
            int thisDigit = *(this->numberPtr + this->size - 1);
            int otherDigit = *(other->numberPtr + other->size - 1);

            if (thisDigit > otherDigit) return 1;
            else if (thisDigit < otherDigit) return -1;
        }
    }
    return 0;
}


bigInt *plusMinus(bigInt *firstNumber, bigInt *secondNumber){
    bigInt *longerNumber;
    bigInt *shorterNumber;
    if (firstNumber -> size >= secondNumber -> size) {
        longerNumber = firstNumber;
        shorterNumber = secondNumber;
    } else {
        longerNumber = secondNumber;
        shorterNumber = firstNumber;
    }
    bigInt *result;
    if (longerNumber -> isPositive == shorterNumber -> isPositive) result = add(longerNumber, shorterNumber);
    else result = subtract(longerNumber, shorterNumber);
    result -> isPositive = longerNumber -> isPositive;
    return result;
}

bigInt *plus(bigInt *firstNumber, bigInt *secondNumber) {
    return plusMinus(firstNumber, secondNumber);
}

bigInt *minus(bigInt *firstNumber, bigInt *secondNumber) {
    return plusMinus(firstNumber, secondNumber);
}





int sum(int firstDigit, int secondDigit, int *inMem) {
    int tempSum = firstDigit + secondDigit + *inMem;
    if (tempSum >= 10) {
        *inMem = 1;
        return tempSum - 10;
    } else {
        *inMem = 0;
        return tempSum;
    }
}


/// Сложение модулей чисел
bigInt *add(bigInt *firstNumber, bigInt *secondNumber) {
    bigInt *bigIntRes = NULL;
    bigIntRes = (bigInt*) malloc(sizeof(bigInt));
    int inMem = 0;

    bigIntRes -> size = firstNumber -> size ;
    bigIntRes -> isPositive = firstNumber -> isPositive ;
    bigIntRes -> numberPtr = (int*) malloc((bigIntRes -> size) * sizeof(int));


    for (int index = 0; index < secondNumber -> size; index++) {
        int firstDigit = *(firstNumber -> numberPtr + index);
        int secondDigit = *(secondNumber -> numberPtr + index);
        *(bigIntRes -> numberPtr + index) = sum(firstDigit, secondDigit, &inMem);
    }
    for (int index = secondNumber -> size; index < firstNumber -> size; index++) {
        int digit = *(firstNumber -> numberPtr + index);
        *(bigIntRes -> numberPtr + index) = sum(digit, 0, &inMem);
    }
    if (inMem != 0) {
        append(bigIntRes, inMem);
        *(bigIntRes -> numberPtr + bigIntRes -> size - 1 ) = inMem;
    }


    return bigIntRes;
}


int difference(int firstDigit, int secondDigit, int *inMem) {
    int tempDiff = firstDigit - secondDigit - *inMem;
    if (tempDiff < 0) {
        *inMem = 1;
        return tempDiff + 10;
    } else {
        *inMem = 0;
        return tempDiff;
    }
}

/// Вычитание модулей чисел
bigInt *subtract(bigInt *firstNumber, bigInt *secondNumber) {
    bigInt *bigIntRes = NULL;
    bigIntRes = (bigInt*) malloc(sizeof(bigInt));
    int inMem = 0;

    bigIntRes -> size = 0 ;
    bigIntRes -> isPositive = firstNumber -> isPositive ;
    bigIntRes -> numberPtr = (int*) malloc(0 * sizeof(int));

    for (int index = 0; index < secondNumber -> size; index++) {
        int firstDigit = *(firstNumber -> numberPtr + index);
        int secondDigit = *(secondNumber -> numberPtr + index);
        append(bigIntRes, difference(firstDigit, secondDigit, &inMem));
    }

    for (int index = secondNumber -> size; index < firstNumber -> size; index++) {
        int firstDigit = *(firstNumber -> numberPtr + index);
        append(bigIntRes, difference(firstDigit, 0, &inMem));
    }
    int lastElement = *(bigIntRes -> numberPtr + bigIntRes -> size - 1 );
    while (lastElement == 0 && bigIntRes -> size > 1) {
        removeLast(bigIntRes);
        lastElement = *(bigIntRes -> numberPtr + bigIntRes -> size - 1 );
    }

    return bigIntRes;
}


///Умножение
bigInt *multiply(bigInt *firstNumber, bigInt *secondNumber) {
    bigInt *bigIntRes = NULL;
    bigIntRes = (bigInt *) malloc(sizeof(bigInt));
    int inMem = 0;

    bigInt *sumToAdd = NULL;
    sumToAdd = (bigInt *) malloc(sizeof(bigInt));
    sumToAdd -> size = 0;
    sumToAdd -> numberPtr = (int*) malloc(0 * sizeof(int));

    bigIntRes -> size = firstNumber -> size +  secondNumber -> size;
    bigIntRes -> isPositive = firstNumber -> isPositive && secondNumber -> isPositive;
    bigIntRes -> numberPtr = (int*) calloc(bigIntRes -> size, sizeof(int));

    for (int position = 0; position < secondNumber -> size; position++) {
        int firstDigit = *(secondNumber -> numberPtr + position);
        for (int index = 0;index < position; index++) append(sumToAdd, 0);
        for (int index = 0; index < firstNumber -> size; index++) {
            int secondDigit = *(firstNumber -> numberPtr + position);

            int multiplication = firstDigit * secondDigit + inMem;
            if (multiplication > 10) {
                inMem = multiplication / 10;
                append(sumToAdd, multiplication % 10);
            } else {
                inMem = 0;
                append(sumToAdd, multiplication);
            }
        }
        if (inMem != 0) append(sumToAdd, inMem);
        inMem = 0;
        bigIntRes = add(bigIntRes, sumToAdd);
        clear(sumToAdd);
    }

    return bigIntRes;
}


///Процесс деления с остатком и целой частью
bigInt *divisionProcess(bigInt *numerator, bigInt *denominator, bool onlyRemains) {
    bigInt *divRes = NULL;
    divRes = (bigInt *) malloc(sizeof(bigInt));

    bigInt *modRes = NULL;
    modRes = (bigInt *) malloc(sizeof(bigInt));
    modRes -> size = 0;
    modRes -> isPositive = true;
    modRes -> numberPtr = (int*) malloc(0 * sizeof(int));

    int initialComp = compareTo(numerator, denominator);
    divRes -> size = 0;
    divRes -> isPositive = numerator -> isPositive && denominator -> isPositive;
    divRes -> numberPtr = (int*) malloc(0 * sizeof(int));

    int index = numerator -> size - 1;
    while (index >= 0) {
        int counter = 0;
        int comparisonRes = compareTo(modRes, denominator);
        while ((comparisonRes == -1 || comparisonRes == 0) && index != -1) {
            int digit = *(numerator -> numberPtr + index);
            insertFirstNumber(modRes, digit);
            index--;
            comparisonRes = compareTo(modRes, denominator);
        }
        while (comparisonRes == 1 || comparisonRes == 0) {
            modRes = subtract(modRes, denominator);
            counter++;
            comparisonRes = compareTo(modRes, denominator);
        }
        append(divRes, counter);
    }

    if (onlyRemains) {
        free(divRes);
        return modRes;
    } else {
        reverse(divRes);
        free(modRes);
        return divRes;
    }
}


/// div
bigInt *myDiv(bigInt *numerator, bigInt *denominator) {

    bigInt *res = divisionProcess(numerator, denominator, false);
    return res;
}


/// mod
bigInt *modResult(bigInt *numerator, bigInt *denominator) {
    bigInt *res = divisionProcess(numerator, denominator, true);
    return res;
}


int *toBigString(bigInt *this ) {
    int *strPtr = (int *) malloc(0 * sizeof(char));
    for (int index = this -> size - 1; index > -1; index++) appendString(strPtr, ((char) *(this -> numberPtr + index)));
    return strPtr;
}

