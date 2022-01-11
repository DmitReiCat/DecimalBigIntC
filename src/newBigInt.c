#include "../include/newBigInt.h"
#include <string.h>
#include <stdlib.h>
#include "stdbool.h"
#include "../include/bigIntAssist.h"
#include <math.h>
#include "../include/consts.h"



/// constructs bigInt from int
bigInt* constructBigIntFromInt(int integer) {
    bigInt *bigIntRes = NULL; bigIntRes = (bigInt*) malloc(sizeof(bigInt));

    if (integer >= 0) {
        bigIntRes->isPositive = true;
    } else {
        bigIntRes->isPositive = false;
        integer *= -1;
    }

    int digitsCounted = digitCount(integer);
    bigIntRes->size = digitsCounted / 8;
    if (digitsCounted % 8 != 0) bigIntRes->size++;
    bigIntRes->digitCount = digitsCounted;
    bigIntRes->numberPtr = (int*)calloc(bigIntRes->size, sizeof(int));

    if (digitsCounted > 8) {
        bigIntRes->numberPtr[1] = integer % WORD_LENGTH;
        bigIntRes->numberPtr[0] = integer / WORD_LENGTH;
    } else {
        bigIntRes->numberPtr[0] = integer % WORD_LENGTH;
    }

    return bigIntRes;
}

/// constructs bigInt from List
bigInt* constructBigIntFromList(listOfInt *list) {
    bigInt *bigIntRes = NULL; bigIntRes = (bigInt*)malloc(sizeof(bigInt));
    bigIntRes->size = list->size;
    bigIntRes->digitCount = bigIntRes->size * 8;
    bigIntRes->numberPtr = (int*)calloc(bigIntRes->size, sizeof(int));

    for (int listBlockIndex = 0; listBlockIndex < list->size; listBlockIndex++) {
        int listBlock = list->numberPtr[listBlockIndex];
        bigIntRes->numberPtr[listBlockIndex] = listBlock;
    }
    bigIntRes->digitCount -= 8 - digitCount(bigIntRes->numberPtr[0]);

    return bigIntRes;
}

/// constructs bigInt from string
bigInt* constructBigIntFromStr(char string[]) {
    bigInt *bigIntRes = NULL; bigIntRes = (bigInt*) malloc(sizeof(bigInt));

    int strSize = (int)strlen(string);
    bigIntRes->size = (strSize - 1) / 8;
    if ((strSize - 1) % 8 != 0) bigIntRes->size += 1;
    bigIntRes->digitCount = strSize - 1;

    int startIndex = 1;
    if (string[0] == '-') {
        bigIntRes->isPositive = false;
    } else if (string[0] == '+') {
        bigIntRes->isPositive = true;
    } else {
        bigIntRes->isPositive = true;
        bigIntRes->size = strSize / 8;
        if (strSize % 8 != 0) bigIntRes->size += 1;
        bigIntRes->digitCount = (int)strlen(string);
        startIndex = 0;
    }
    bigIntRes->numberPtr = (int*)calloc(bigIntRes->size, sizeof(int));

    int arrIndex = 0;
    int digitsToAdd = bigIntRes->digitCount % 8;
    if (digitsToAdd == 0) digitsToAdd = 8;
    for (int i = startIndex; i < (int)strlen(string); i++) {
        int digit = string[i] - '0';
        bigIntRes->numberPtr[arrIndex] *= 10;
        bigIntRes->numberPtr[arrIndex] += digit;
        digitsToAdd--;
        if (digitsToAdd == 0) {
            digitsToAdd = 8;
            arrIndex++;
        }
    }

    return bigIntRes;
}

/// ">" --> 1, "==" --> 0, "<" --> -1
int compareTo(bigInt *this, bigInt *other, bool onlyModules) {
    int negSwitch = 1;
    if (!onlyModules) {
        if (this->isPositive == false && other->isPositive == true) return -1;
        else if (this->isPositive == true && other->isPositive == false) return 1;
        else if (this->isPositive == false && other->isPositive == false) negSwitch = -1;
    }

    if (this->size > other->size || this->digitCount > other->digitCount) return 1 * negSwitch;
    else if (this->size < other->size || this->digitCount < other->digitCount) return -1 * negSwitch;
    else {
        for (int index = this->size; index > 0; index--) {
            int thisDigit = this->numberPtr[this->size - 1];
            int otherDigit = other->numberPtr[other->size - 1];

            if (thisDigit > otherDigit) return 1 * negSwitch;
            else if (thisDigit < otherDigit) return -1 * negSwitch;
        }
    }
    return 0;
}


/// Sum and diff of numbers' modules
bigInt* moduleUnited(bigInt *firstNumber, bigInt *secondNumber, bool isSum) {
    bigInt *bigIntRes = NULL; bigIntRes = (bigInt *) malloc(sizeof(bigInt));
    int inMem = 0;

    bigIntRes->size = firstNumber->size;
    bigIntRes->isPositive = firstNumber->isPositive;
    bigIntRes->numberPtr = (int*) malloc((bigIntRes -> size) * sizeof(int));
    bigIntRes->digitCount = 0;
    int blockDiff = firstNumber->size - secondNumber->size;

    for (int blockIndex = secondNumber->size - 1; blockIndex >= 0; blockIndex--) {
        int firstBlock = firstNumber->numberPtr[blockDiff + blockIndex];
        int secondBlock = secondNumber->numberPtr[blockIndex];
        if (isSum) bigIntRes->numberPtr[blockDiff + blockIndex] = blockSum(firstBlock, secondBlock, &inMem);
        else bigIntRes->numberPtr[blockDiff + blockIndex] = blockSubtraction(firstBlock, secondBlock, &inMem);
        bigIntRes->digitCount += 8;
    }
    for (int blockIndex = blockDiff - 1; blockIndex >= 0; blockIndex--) {
        int block = firstNumber->numberPtr[blockIndex];
        if (isSum) bigIntRes->numberPtr[blockIndex] = blockSum(block, 0, &inMem);
        else bigIntRes->numberPtr[blockIndex] = blockSubtraction(block, 0, &inMem);
        bigIntRes->digitCount += 8;
    }
    if (isSum) {
        if (inMem != 0) insertToZeroBlock(bigIntRes, inMem);
    } else
        deleteExtraZeroBlocks(bigIntRes);
    bigIntRes->digitCount -= 8 - digitCount(bigIntRes->numberPtr[0]);
    return bigIntRes;
}

/// Default "+" option
bigInt* plus(bigInt *firstNumber, bigInt *secondNumber) {
    return plusMinus(firstNumber, secondNumber,false);
}
/// Default "-" option
bigInt* minus(bigInt *firstNumber, bigInt *secondNumber) {
    return plusMinus(firstNumber, secondNumber, true);
}


/// multiplication of bigInts
bigInt *multiplyBigInts(bigInt *firstNumber, bigInt *secondNumber) {
    listOfInt *reversedListRes = constructEmptyList();
    int position = 0;
    int offset = 0;
    for (int secondBlockIndex = secondNumber->size - 1; secondBlockIndex >= 0; secondBlockIndex--) {
        int secondBlock = secondNumber->numberPtr[secondBlockIndex];
        for (int firstBlockIndex = firstNumber->size - 1; firstBlockIndex >= 0; firstBlockIndex--, offset++) {
            int firstBlock =  firstNumber->numberPtr[firstBlockIndex];
            long long int result = (long long int)firstBlock * (long long int)secondBlock;
            listAddReversed(reversedListRes, position + offset, result);
        }
        position++; offset = 0;
    }
    reverseList(reversedListRes);
    bigInt *bigIntRes = constructBigIntFromList(reversedListRes);
    bigIntRes->isPositive = (firstNumber->isPositive == secondNumber->isPositive);

    freeList(reversedListRes);
    return bigIntRes;
}


/// converts bigint to string
char* bigIntToString(bigInt *this) {
    char *result;
    int i = 1;
    result = (char*)malloc(sizeof(char));
    if (this->isPositive) result[0] = '+';
    else result[0] = '-';

    int digitsToAdd = this->digitCount % 8;
    if (digitsToAdd == 0) digitsToAdd = 8;
    for (int blockIndex = 0; blockIndex < this->size; blockIndex++) {
        int number = this->numberPtr[blockIndex];
        for (int indexInBlock = 0; digitsToAdd > 0; indexInBlock++) {
            char digit = (number % myPow(10, digitsToAdd) / myPow(10, digitsToAdd - 1)) + '0';
            result = (char*) realloc(result, (i + 1) * sizeof(char));
            result[i] = digit;
            i++;
            digitsToAdd--;
        }
        digitsToAdd = 8;
    }
    result = (char*) realloc(result, (i + 1) * sizeof(char));
    result[i] = '\0';

    return result;
}


/// converts bigint to string
int bigIntToInt(bigInt *this) {
    int result = 0;

    for (int blockIndex = 0; blockIndex < this->size; blockIndex++) {
        int number = this->numberPtr[blockIndex];
        result *= WORD_LENGTH;
        result += number;
    }

    if (!this->isPositive) result *= -1;
    return result;
}

bigInt *divisionProcess(bigInt *nominator, bigInt *denominator, bool onlyRemains) {
    bigInt *modRes = NULL; modRes = (bigInt *) malloc(sizeof(bigInt));
    modRes->size = 0;
    modRes->digitCount = 0;
    modRes->isPositive = true;
    modRes->numberPtr = NULL;
    bool modSign = nominator->isPositive;

    bigInt *divRes = NULL; divRes = (bigInt *) malloc(sizeof(bigInt));
    divRes->size = 0;
    divRes->digitCount = 0;
    divRes->isPositive = true;
    divRes->numberPtr = NULL;
    bool divSign = nominator->isPositive == denominator->isPositive;

    bool isFirstNonZeroMet = false;

    int digitsToAddFromBlock = nominator->digitCount % 8;
    if (digitsToAddFromBlock == 0) digitsToAddFromBlock = 8;
    int modTen = myPow(10, digitsToAddFromBlock);
    int divTen = myPow(10, digitsToAddFromBlock - 1);

    for (int firstBlockIndex = 0; firstBlockIndex < nominator->size; firstBlockIndex++, digitsToAddFromBlock = 8) {
        int firstBlock = nominator->numberPtr[firstBlockIndex];
        int comparisonRes = compareTo(modRes, denominator, true);
        for (int unusedDigitInBlock = digitsToAddFromBlock; unusedDigitInBlock > 0;) {
            while (comparisonRes < 0 && modTen >= 10) {
                int digit = firstBlock % modTen / divTen;
                modRes = appendBigIntByDigit(modRes, digit);
                comparisonRes = compareTo(modRes, denominator, true);
                if (comparisonRes < 0 && isFirstNonZeroMet) divRes = appendBigIntByDigit(divRes, 0);
                modTen /= 10;
                divTen /= 10;
                unusedDigitInBlock--;
            }
            int counter = 0;
            if (comparisonRes >= 0) {
                while (comparisonRes >= 0) {
                    isFirstNonZeroMet = true;
                    bigInt *tmpBigInt = NULL; tmpBigInt = (bigInt *) malloc(sizeof(bigInt));
                    tmpBigInt = moduleUnited(modRes, denominator, false);
                    freeBigInt(modRes);
                    modRes = tmpBigInt;
                    counter++;
                    comparisonRes = compareTo(modRes, denominator, true);
                }
                divRes = appendBigIntByDigit(divRes, counter);
            }
        }
        modTen = WORD_LENGTH; divTen = WORD_LENGTH / 10;
    }

    if (onlyRemains) {
        modRes->isPositive = modSign;
        freeBigInt(divRes);
        return modRes;
    } else {
        if (divRes->size == 0) {
            freeBigInt(divRes);
            divRes = constructBigIntFromInt(0);
        }
        divRes->isPositive = divSign;
        freeBigInt(modRes);
        return divRes;
    }
}


/// div
bigInt *bigIntDiv(bigInt *numerator, bigInt *denominator) {
    bigInt *res = divisionProcess(numerator, denominator, false);
    return res;
}


/// mod
bigInt *bigIntMod(bigInt *numerator, bigInt *denominator) {
    bigInt *res = divisionProcess(numerator, denominator, true);
    return res;
}


/// frees memory taken by bigInt
void freeBigInt(bigInt *this) {
    free(this->numberPtr);
    free(this);
}