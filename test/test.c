#include <assert.h>
#include <corecrt_malloc.h>
#include <stdio.h>
//#include "../include/bigInt.h"
#include "../include/newBigInt.h"
#include "../include/bigIntAssist.h"
#include "../include/list.h"
#include <string.h>
#include <stdlib.h>


void assertConstructInt(int number) {
    newBigInt *bigNum = constructBigIntFromInt(number);
    assert(number == bigIntToInt(bigNum));
    printf("  //success on converting %d\n", number);
    freeBigInt(bigNum);
}

void assertConstructStr(char number[]) {
    newBigInt *bigNum = constructBigIntFromStr(number);
    int preRes = strcmp(number, bigIntToString(bigNum));
    assert(0 == preRes);
    printf("  //success on converting %s\n", number);
    freeBigInt(bigNum);
}


void constructAndToStringTest() {
    printf("conversion testing...\n");
    for (int number = 10; number <= 1000000000; number *= 10) {
        assertConstructInt(number);
    }
    for (int number = -10; number >= -1000000000; number *= 10) {
        assertConstructInt(number);
    }
    assertConstructInt(1234567890);
    assertConstructInt(0);
    assertConstructInt(100000000);
    assertConstructStr("+1234567890");
    assertConstructStr("+0");
    assertConstructStr("-1234567890");
    assertConstructStr("+100000000");
    assertConstructStr("-100000000");
    assertConstructStr("-1345678236412341234123414");

    printf("conversion testing successful!\n\n");
}


void assertModuleSumFromInt(int firstNumber, int secondNumber) {
    newBigInt *firstBigNum = constructBigIntFromInt(firstNumber);
    newBigInt *secondBigNum = constructBigIntFromInt(secondNumber);
    newBigInt *result = moduleSum(firstBigNum, secondBigNum, true);
    printf("  //trying to %d + %d", firstNumber, secondNumber);
//    printBigInt(result);
//    printf("size= %d, digitCount= %d\n", result->size, result->digitCount);
//    printBigInt(result);
//    printf("result = %d, bigNum = %d", firstNumber+ secondNumber, bigIntToInt(result));
    assert(firstNumber + secondNumber == bigIntToInt(result));
    printf("  (yoshi!)\n");
    freeBigInt(result);
}


void moduleSumTest() {
    printf("moduleSum testing...\n");
    for (int firstNum = 9; firstNum <= 1000000000; firstNum *= 10, firstNum += 9) {
        assertModuleSumFromInt(firstNum, 9);
    }

    // overflow from string test
    newBigInt *firstBigNum = constructBigIntFromStr("999999999999999999999999");
    newBigInt *secondBigNum = constructBigIntFromStr("999999999999999999999999");
    newBigInt *result = moduleSum(firstBigNum, secondBigNum, true);
    printf("  //trying to %s", "999999999999999999999999 x2");
    printBigInt(result);
    printf("size= %d, digitCount= %d\n", result->size, result->digitCount);
    int preRes = strcmp("+1999999999999999999999998", bigIntToString(result));
    assert(0 == preRes);
    printf("  (yoshi!)\n");
    freeBigInt(result);

    printf("moduleSum testing successful!\n\n");
}

void assertModuleDiffFromInt(int firstNumber, int secondNumber) {
    newBigInt *firstBigNum = constructBigIntFromInt(firstNumber);
    newBigInt *secondBigNum = constructBigIntFromInt(secondNumber);
    newBigInt *result = moduleDiff(firstBigNum, secondBigNum, true);
    printf("  //trying to %d - %d", firstNumber, secondNumber);
    assert(firstNumber - secondNumber == bigIntToInt(result));
    printf("  (yoshi!)\n");
//    printBigInt(result);
//    printf("size= %d, digitCount= %d\n", result->size, result->digitCount);
    freeBigInt(result);
}


void moduleDiffTest() {
    printf("moduleDiff testing...\n");
    for (int number = 1; number <= 1000000000; number *= 10) {
        assertModuleDiffFromInt(number, 1);
    }
    for (int number = 10; number <= 1000000000; number *= 10) {
        assertModuleDiffFromInt(1000000000, number);
    }
    assertModuleDiffFromInt(354, 40);
    printf("moduleDiff testing successful!\n\n");
}

void assertPlusFromInt(int firstNumber, int secondNumber) {
    newBigInt *firstBigNum = constructBigIntFromInt(firstNumber);
    newBigInt *secondBigNum = constructBigIntFromInt(secondNumber);
    newBigInt *result = plus(firstBigNum, secondBigNum, true);
    printf("  //trying to %d + %d", firstNumber, secondNumber);
    assert(firstNumber + secondNumber == bigIntToInt(result));
    printf("  (yoshi!)\n");
//    printBigInt(result);
//    printf("size= %d, digitCount= %d\n", result->size, result->digitCount);
    freeBigInt(result);
}

void assertMinusFromInt(int firstNumber, int secondNumber) {
    newBigInt *firstBigNum = constructBigIntFromInt(firstNumber);
    newBigInt *secondBigNum = constructBigIntFromInt(secondNumber);
    newBigInt *result = minus(firstBigNum, secondBigNum, true);
    printf("  //trying to %d - %d", firstNumber, secondNumber);
    assert(firstNumber - secondNumber == bigIntToInt(result));
    printf("  (yoshi!)\n");
    freeBigInt(result);
}


void plusMinusTests() {
    printf("plusMinus testing...\n");
    for (int number = 1; number <= 1000000000; number *= 10) {
        assertPlusFromInt(number, -1);
    }
    for (int number = 1; number <= 1000000000; number *= 10) {
        assertMinusFromInt(-1, number);
    }
    for (int number = 10; number <= 1000000000; number *= 10) {
        assertMinusFromInt(1000000000, number * -1);
    }
    for (int number = 10; number <= 1000000000; number *= 10) {
        assertPlusFromInt(number * -1, 1000000000);
    }
    for (int firstNum = 9; firstNum <= 1000000000; firstNum *= 10, firstNum += 9) {
        assertPlusFromInt(firstNum, 9);
    }
    for (int firstNum = 9; firstNum <= 1000000000; firstNum *= 10, firstNum += 9) {
        assertMinusFromInt(firstNum, 9);
    }
    printf("plusMinus testing successful!\n\n");
}


void assertMultiplication(int firstNumber, int secondNumber) {
    newBigInt *firstBigNum = constructBigIntFromInt(firstNumber);
    newBigInt *secondBigNum = constructBigIntFromInt(secondNumber);
    newBigInt *result = multiplyBigInts(firstBigNum, secondBigNum);
    printf("  //trying to %d * %d", firstNumber, secondNumber);
//    printBigInt(result);                                                                                                        //Debug
//    printf("size= %d, digitCount= %d\n, compare to %d", result->size, result->digitCount, firstNumber * secondNumber);   //Debug
    assert(firstNumber * secondNumber == bigIntToInt(result));
    printf("  (yoshi!)\n");
    freeBigInt(firstBigNum);
    freeBigInt(secondBigNum);
    freeBigInt(result);
}

void assertMultiplicationFromString(char firstNumber[], char secondNumber[], char resultString[]) {
    newBigInt *firstBigNum = constructBigIntFromStr(firstNumber);
    newBigInt *secondBigNum = constructBigIntFromStr(secondNumber);
    newBigInt *result = multiplyBigInts(firstBigNum, secondBigNum);
    printf("  //trying to %s * %s", firstNumber, secondNumber);
    int preRes = strcmp(resultString, bigIntToString(result));
    assert(0 == preRes);
    printf("  (yoshi!)\n");
    freeBigInt(firstBigNum);
    freeBigInt(secondBigNum);
    freeBigInt(result);
}


void multiplicationTests() {

    assertMultiplication(12345657, 12);
    assertMultiplication(50, 10000000);
    /// sign test
    assertMultiplication(-5, -5);
    assertMultiplication(5, -5);
    assertMultiplication(-5, 5);
    assertMultiplication(5, 5);
    /// test
    assertMultiplication(100000000, 5);
    assertMultiplication(5, 100000000);
    assertMultiplication(50, 1000000);
    assertMultiplication(500, 1000000);
    assertMultiplicationFromString(
            "500",
            "1000000",
            "+500000000"
            );
    assertMultiplicationFromString(
            "50000000000",
            "10000000000000000000000",
            "+500000000000000000000000000000000"
            );
    assertMultiplicationFromString(
            "918237461982376124112341581265",
            "1982734091827487",
            "+1820620720265603145165397238824311603171231055"
            );
}

void assistTest() {
//    printf("test fromInt\n");
    newBigInt *bigNum = constructBigIntFromStr("1");
    printBigInt(bigNum);
    deleteExtraZeroBlocks(bigNum);
    printBigInt(bigNum);

//    printf("test insertAndSetZeroBlock\n");
//    newBigInt *bigNum = constructBigIntFromStr("99999999999999999");
//    insertToZeroBlock(bigNum, 687);
//    printBigInt(bigNum);
//    printf("digitCount = %d\n", digitCount(0));
//    printf("digitCount = %d\n", digitCount(10));
//    printf("digitCount = %d\n", digitCount(20));
//    printf("digitCount = %d\n", digitCount(99));
//    printf("digitCount = %d\n", digitCount(999999));
    freeBigInt(bigNum);
}


int main() {
    listOfInt *myList = constructEmptyList();
    listAppend(myList, 123456789);
    listPrint(myList);
    newBigInt *bigNum = constructBigIntFromReversedList(myList);
    printBigInt(bigNum);
    newBigInt *bigNum2 = constructBigIntFromInt(1);
    bigNum = plus(bigNum, bigNum2, true);
    printBigInt(bigNum);
    freeBigInt(bigNum);



    assistTest();
    constructAndToStringTest();
    moduleSumTest();
    moduleDiffTest();
    plusMinusTests();
    multiplicationTests();
    return 0;
}