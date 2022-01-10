#include "../include/newBigInt.h"
#include <string.h>
#include <stdlib.h>
#include "stdbool.h"
#include "../include/bigIntAssist.h"
#include <math.h>

//TODO delete digitCount dependency

/// constructs bigInt from int
bigigInt* constructBigIntFromInt(int integer) {
    bigigInt *bigIntRes = NULL;
    bigIntRes = (bigigInt*) malloc(sizeof(bigigInt));

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

    int arrIndex = 0;
    int digitsToAdd = bigIntRes->digitCount % 8;
    if (digitsToAdd == 0) digitsToAdd = 8;

    for (int i = 0; i < digitsCounted; i++) {
        int digit = (integer % myPow(10, digitsCounted - i) / myPow(10, digitsCounted - i - 1));
        *(bigIntRes->numberPtr + arrIndex) *= 10;
        *(bigIntRes->numberPtr + arrIndex) += digit;
        digitsToAdd--;
         if (digitsToAdd == 0) {
            digitsToAdd = 8;
            arrIndex++;
        }
    }

    return bigIntRes;
}
/// constructs bigInt from reversedList
bigigInt* constructBigIntFromReversedList(listOfInt *list) {
    bigigInt *bigIntRes = NULL;
    bigIntRes = (bigigInt*)malloc(sizeof(bigigInt));
    double size = ceil((double)list->size / 8.0);
    bigIntRes->size = (int)size;
    bigIntRes->digitCount = 0;
    bigIntRes->numberPtr = (int*)calloc(bigIntRes->size, sizeof(int));


    int numberPos = bigIntRes->size * 8 - list->size;
    int blockPos = 0;
    if (list->size % 8 == 0) blockPos = -1;
    for (int listIndex = list->size - 1; listIndex >= 0 ; listIndex--) {
        if (numberPos % 8 == 0) {
            blockPos++;
        }
        *(bigIntRes->numberPtr + blockPos) *= 10;
        *(bigIntRes->numberPtr + blockPos) += *(list->numberPtr + listIndex);
        bigIntRes->digitCount++;
        numberPos++;
    }
    freeList(list);
    return bigIntRes;
}
/// constructs bigInt from List
bigigInt* constructBigIntFromList(listOfInt *list) {
    bigigInt *bigIntRes = NULL;
    bigIntRes = (bigigInt*)malloc(sizeof(bigigInt));
    double size = ceil((double)list->size / 8.0);
    bigIntRes->size = (int)size;
    bigIntRes->digitCount = 0;
    bigIntRes->numberPtr = (int*)calloc(bigIntRes->size, sizeof(int));

    int firstNonZero = 0;
    while(*(list->numberPtr + firstNonZero) == 0) firstNonZero++;

    int numberPos = bigIntRes->size * 8 - list->size;
    int blockPos = 0;
    if (list->size % 8 == 0) blockPos = -1;
    for (int listIndex = firstNonZero; listIndex < list->size ; listIndex++) {
        if (numberPos % 8 == 0) {
            blockPos++;
        }
        *(bigIntRes->numberPtr + blockPos) *= 10;
        *(bigIntRes->numberPtr + blockPos) += *(list->numberPtr + listIndex);
        bigIntRes->digitCount++;
        numberPos++;
    }
    return bigIntRes;
}
/// constructs bigInt from string
bigigInt* constructBigIntFromStr(char string[]) {
    bigigInt *bigIntRes = NULL;
    bigIntRes = (bigigInt*) malloc(sizeof(bigigInt));

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
        *(bigIntRes->numberPtr + arrIndex) *= 10;
        *(bigIntRes->numberPtr + arrIndex) += digit;
        digitsToAdd--;
        if (digitsToAdd == 0) {
            digitsToAdd = 8;
            arrIndex++;
        }
    }

    return bigIntRes;
}

/// ">" --> 1, "==" --> 0, "<" --> -1
int compareTo(bigigInt *this, bigigInt *other) {
    if (this->size > other->size || this->digitCount > other->digitCount) return 1;
    else if (this->size < other->size || this->digitCount < other->digitCount) return -1;
    else {
        for (int index = this->size; index > 0; index--) {
            int thisDigit = *(this->numberPtr + this->size - 1);
            int otherDigit = *(other->numberPtr + other->size - 1);

            if (thisDigit > otherDigit) return 1;
            else if (thisDigit < otherDigit) return -1;
        }
    }
    return 0;
}


/// Sum of numbers' modules
bigigInt* moduleSum(bigigInt *firstNumber, bigigInt *secondNumber, bool freeMem) {
    bigigInt *bigIntRes = NULL;
    bigIntRes = (bigigInt*) malloc(sizeof(bigigInt));
    int inMem = 0;

    bigIntRes->size = firstNumber->size;
    bigIntRes->isPositive = firstNumber->isPositive;
    bigIntRes->numberPtr = (int*) malloc((bigIntRes -> size) * sizeof(int));
    bigIntRes->digitCount = 0;
    int blockDiff = firstNumber->size - secondNumber->size;

    for (int blockIndex = secondNumber->size - 1; blockIndex >= 0; blockIndex--) {
        int firstBlock = *(firstNumber->numberPtr + (blockDiff + blockIndex));
        int secondBlock = *(secondNumber->numberPtr + blockIndex);
        *(bigIntRes->numberPtr + (blockDiff + blockIndex)) = blockSum(firstBlock, secondBlock, &inMem);
        bigIntRes->digitCount += 8;
    }
    for (int blockIndex = blockDiff - 1; blockIndex >= 0; blockIndex--) {
        int block = *(firstNumber->numberPtr + blockIndex);
        *(bigIntRes->numberPtr + blockIndex) = blockSum(block, 0, &inMem);
        bigIntRes->digitCount += 8;
    }
    if (inMem != 0) {
        insertToZeroBlock(bigIntRes, inMem);
    }
    bigIntRes->digitCount -= 8 - digitCount(*(bigIntRes->numberPtr));
    if (freeMem == true) {
        freeBigInt(firstNumber);
        freeBigInt(secondNumber);
    }
    return bigIntRes;
}


/// Difference of numbers' modules
bigigInt* moduleDiff(bigigInt *firstNumber, bigigInt *secondNumber, bool freeMem) {
    bigigInt *bigIntRes = NULL;
    bigIntRes = (bigigInt *) malloc(sizeof(bigigInt));
    int inMem = 0;

    bigIntRes->size = firstNumber->size;
    bigIntRes->isPositive = firstNumber->isPositive;
    bigIntRes->numberPtr = (int *) malloc((bigIntRes->size) * sizeof(int));
    bigIntRes->digitCount = 0;
    int blockDiff = firstNumber->size - secondNumber->size;

    for (int blockIndex = secondNumber->size - 1; blockIndex >= 0; blockIndex--) {
        int firstBlock = *(firstNumber->numberPtr + (blockDiff + blockIndex));
        int secondBlock = *(secondNumber->numberPtr + blockIndex);
        *(bigIntRes->numberPtr + (blockDiff + blockIndex)) = blockSubtraction(firstBlock, secondBlock, &inMem);
        bigIntRes->digitCount += 8;
    }
    for (int blockIndex = blockDiff - 1; blockIndex >= 0; blockIndex--) {
        int block = *(firstNumber->numberPtr + blockIndex);
        *(bigIntRes->numberPtr + blockIndex) = blockSubtraction(block, 0, &inMem);
        bigIntRes->digitCount += 8;
    }
    deleteExtraZeroBlocks(bigIntRes);
    bigIntRes->digitCount -= 8 - digitCount(*(bigIntRes->numberPtr));
    if (freeMem == true) {
        freeBigInt(firstNumber);
        freeBigInt(secondNumber);
    }
    return bigIntRes;
}

/// Default "+" option
bigigInt* plus(bigigInt *firstNumber, bigigInt *secondNumber, bool freeMem) {
    return plusMinus(firstNumber, secondNumber, freeMem);
}
/// Default "-" option
bigigInt* minus(bigigInt *firstNumber, bigigInt *secondNumber, bool freeMem) {
    secondNumber->isPositive = !secondNumber->isPositive;
    return plusMinus(firstNumber, secondNumber, freeMem);
}


/// multiplication of bigInts
bigigInt *multiplyBigInts(bigigInt *firstNumber, bigigInt *secondNumber, bool freeMem) {
    listOfInt *reversedListRes = constructEmptyList();
    int position = 0;
    int offset = 0;
    for (int secondBlockIndex = secondNumber->size -1; secondBlockIndex >= 0; secondBlockIndex --) {
        int secondBlock = *(secondNumber->numberPtr + secondBlockIndex);
        for (int secondDigitIndex = 0; secondDigitIndex < 8; secondDigitIndex++, position++, offset = 0) {
            int secondDigit = secondBlock % myPow(10, secondDigitIndex + 1) / myPow(10, secondDigitIndex);
            for (int firstBlockIndex = firstNumber->size -1; firstBlockIndex >= 0; firstBlockIndex --) {
                int firstBlock =  *(firstNumber->numberPtr + firstBlockIndex);
                for (int firstIndexDigit = 0; firstIndexDigit < 8; firstIndexDigit++, offset++) {
                    int firstDigit = firstBlock % myPow(10, firstIndexDigit + 1) / myPow(10, firstIndexDigit);
                    listAddReversed(reversedListRes, position + offset, firstDigit * secondDigit);
                }
            }
        }
    }
    removeZerosFromEnd(reversedListRes);
    bigigInt *bigIntRes = constructBigIntFromReversedList(reversedListRes);
    bool sign = !(!firstNumber->isPositive && secondNumber->isPositive || firstNumber->isPositive && !secondNumber->isPositive);
    if (freeMem) {
        freeBigInt(firstNumber);
        freeBigInt(secondNumber);
    }
    bigIntRes->isPositive = sign;
    return bigIntRes;
}





/// converts bigint to string
char* bigIntToString(bigigInt *this) {
    char *result;
    int i = 1;
    result = (char*)malloc(sizeof(char));

    if (this->isPositive) result[0] = '+';
    else result[0] = '-';

    int digitsToAdd = this->digitCount % 8;
    if (digitsToAdd == 0) digitsToAdd = 8;
    for (int blockIndex = 0; blockIndex < this->size; blockIndex++) {
        int number = *(this->numberPtr + blockIndex);
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
int bigIntToInt(bigigInt *this) {
    //TODO comparing for safe conversion
    int result = 0;

    int digitsToAdd = this->digitCount % 8;
    if (digitsToAdd == 0) digitsToAdd = 8;
    for (int blockIndex = 0; blockIndex < this->size; blockIndex++) {
        int number = *(this->numberPtr + blockIndex);
        for (int indexInBlock = 0; digitsToAdd > 0; indexInBlock++) {
            int digit = number % myPow(10, digitsToAdd) / myPow(10, digitsToAdd - 1);
            result *= 10;
            result += digit;
            digitsToAdd--;
        }
        digitsToAdd = 8;
    }

    if (!this->isPositive) result *= -1;
    return result;
}

bigigInt *divisionProcess(bigigInt *nomerator, bigigInt *denominator, bool onlyRemains) {
//    bigigInt *divRes = NULL;
//    divRes = (bigigInt *) malloc(sizeof(bigigInt));
//    divRes -> isPositive = true;
//    divRes -> size = 0;
//    divRes -> isPositive = true;
//    divRes -> numberPtr = (int*) malloc(0 * sizeof(int));
    listOfInt *divResList = constructEmptyList();

    bigigInt *modRes = NULL;
    modRes = (bigigInt *) malloc(sizeof(bigigInt));
    modRes -> size = 0;
    modRes -> digitCount = 0;
    modRes -> isPositive = true;
    modRes -> numberPtr = NULL;


//    bigigInt *tmpNuminator = NULL;
//    tmpNuminator = (bigigInt *) malloc(sizeof(bigigInt));
//    tmpNuminator -> isPositive = true;
//    tmpNuminator -> size = 0;
//    tmpNuminator->digitCount = 0;
    listOfInt *tmpNominatorList = constructEmptyList();


    int digitsToAddFromBlock = nomerator->digitCount % 8;
    if (digitsToAddFromBlock == 0) digitsToAddFromBlock = 8;
    int modTen = myPow(10, digitsToAddFromBlock);
    int divTen = myPow(10, digitsToAddFromBlock - 1);

    for (int firstBlockIndex = 0; firstBlockIndex < nomerator->size; firstBlockIndex++, modTen = 100000000, divTen = 10000000, digitsToAddFromBlock = 8) {
        int firstBlock = *(nomerator->numberPtr + firstBlockIndex);
        int counter = 0;
        int comparisonRes = compareTo(modRes, denominator);
        for (int unusedDigitInBlock = digitsToAddFromBlock; unusedDigitInBlock > 0;) {

            while (comparisonRes <= 0 && modTen >= 10) {
                int digit = firstBlock % modTen / divTen;
                appendBigIntByDigit(modRes, digit);
                comparisonRes = compareTo(modRes, denominator);
                modTen /= 10;
                divTen /= 10;
                unusedDigitInBlock--;
            }
            if (comparisonRes >= 0) {
                while (comparisonRes >= 0) {
                    modRes = moduleDiff(modRes, denominator, false); // todo memory management (free only denominator)
                    counter++;
                    comparisonRes = compareTo(modRes, denominator);
                }
//            freeList(tmpNominatorList);
            }

        }

//        listAppend(divResList, counter);
    }


//    int index = nomerator -> size - 1;
//    while (index >= 0) {
//        int counter = 0;
//        int comparisonRes = compareTo(modRes, denominator);
//        while ((comparisonRes == -1 || comparisonRes == 0) && index != -1) {
//            int digit = *(nomerator -> numberPtr + index);
//            insertAndSetZeroBlock(modRes, digit);
//            index--;
//            comparisonRes = compareTo(modRes, denominator);
//        }
//        while (comparisonRes == 1 || comparisonRes == 0) {
//            modRes = subtract(modRes, denominator);
//            counter++;
//            comparisonRes = compareTo(modRes, denominator);
//        }
//        append(divRes, counter);
//
//    }
//
//    if (onlyRemains) {
//        free(divRes);
//        printf("0");
//        return modRes;
//    } else {
//        divRes -> isPositive = nomerator -> isPositive == denominator -> isPositive;
//        reverse(divRes);
//        free(modRes);
//        return divRes;
//    }
    return modRes;
}


///// div
//bigInt *myDiv(bigInt *numerator, bigInt *denominator) {
//
//    bigInt *res = divisionProcess(numerator, denominator, false);
//    return res;
//}
//
//
///// mod
//bigInt *modResult(bigInt *numerator, bigInt *denominator) {
//    bigInt *res = divisionProcess(numerator, denominator, true);
//    return res;
//}


/// frees memory taken by bigInt
void freeBigInt(bigigInt *this) {
    free(this->numberPtr);
    free(this);
}