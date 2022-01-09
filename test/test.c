#include <assert.h>
#include <corecrt_malloc.h>
#include <stdio.h>
//#include "../include/bigInt.h"
#include "../include/newBigInt.h"
#include "../include/bigIntAssist.h"
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

    int number = 10;
    while (number <= 1000000000) {
        assertConstructInt(number);
        number *= 10;
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
    newBigInt *result = moduleSum(firstBigNum, secondBigNum);
    printf("  //trying to %d + %d", firstNumber, secondNumber);
//    printBigInt(result);
//    printf("result = %d, bigNum = %d", firstNumber+ secondNumber, bigIntToInt(result));
    assert(firstNumber + secondNumber == bigIntToInt(result));
    printf("  (yoshi!)\n");
    freeBigInt(firstBigNum);
    freeBigInt(secondBigNum);
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
    newBigInt *result = moduleSum(firstBigNum, secondBigNum);
    printf("  //trying to %s", "999999999999999999999999 x2");
    int preRes = strcmp("+1999999999999999999999998", bigIntToString(result));
    assert(0 == preRes);
    printf("  (yoshi!)\n");
    freeBigInt(firstBigNum);
    freeBigInt(secondBigNum);
    freeBigInt(result);

    printf("moduleSum testing successful!\n\n");
}

void assertModuleDiffFromInt(int firstNumber, int secondNumber) {
    newBigInt *firstBigNum = constructBigIntFromInt(firstNumber);
    newBigInt *secondBigNum = constructBigIntFromInt(secondNumber);
    newBigInt *result = moduleDiff(firstBigNum, secondBigNum);
    printf("  //trying to %d - %d", firstNumber, secondNumber);
    assert(firstNumber - secondNumber == bigIntToInt(result));
    printf("  (yoshi!)\n");
//    printBigInt(result);
//    printf("size= %d, digitCount= %d\n", result->size, result->digitCount);
    freeBigInt(firstBigNum);
    freeBigInt(secondBigNum);
    freeBigInt(result);
}


void moduleDiffTest() {
    printf("moduleDiff testing...\n");
    for (int number = 1; number <= 1000000000; number *= 10) {
        assertModuleDiffFromInt(number, 1);
    }

    assertModuleDiffFromInt(354, 40);
    assertModuleDiffFromInt(1000000000, 1000000000);
    printf("moduleDiff testing successful!\n\n");
}

//
//void multiplicationTests() {
//
//
//
//
//    bigInt *firstNumber = constructBigIntFromStr("-5");
//    bigInt *secondNumber = constructBigIntFromStr("91");
//    bigInt *result = multiply(firstNumber, secondNumber);
//    assert(-455 == toInt(result));
//    clear(firstNumber);
//    clear(secondNumber);
//    clear(result);
//
//
//    firstNumber = constructBigIntFromStr("-5545");
//    secondNumber = constructBigIntFromStr("9000001");
//    result = multiply(firstNumber, secondNumber);
//    int preRes = strcmp("-49905005545", bigIntToString(result));
//    assert(0 == preRes);
//    clear(firstNumber);
//    clear(secondNumber);
//    clear(result);
//
//
//    firstNumber = constructBigIntFromStr("-1000");
//    secondNumber = constructBigIntFromStr("9");
//    result = multiply(firstNumber, secondNumber);
//    preRes = strcmp("-9000", bigIntToString(result));
//    assert(0 == preRes);
//    clear(firstNumber);
//    clear(secondNumber);
//    clear(result);
//
//}
//
//void divAndModTest() {
//    bigInt *firstNumber = constructBigIntFromStr("-91");
//    bigInt *secondNumber = constructBigIntFromStr("5");
//    bigInt *result = myDiv(firstNumber, secondNumber);
//    bigInt *result2 = modResult(firstNumber, secondNumber);
//
//    assert(-18 == toInt(result));
//    assert(1 == toInt(result2));
//    clear(firstNumber);
//    clear(secondNumber);
//    clear(result);
//    clear(result2);
//
//    firstNumber = constructBigIntFromStr("-10000");
//    secondNumber = constructBigIntFromStr("200");
//    result = myDiv(firstNumber, secondNumber);
//    assert(-50 == toInt(result));
//    result2 = modResult(firstNumber, secondNumber);
//    assert(0 == toInt(result2));
//    clear(firstNumber);
//    clear(secondNumber);
//    clear(result);
//    clear(result2);
//
//    firstNumber = constructBigIntFromStr("1000");
//    secondNumber = constructBigIntFromStr("-7");
//    result = myDiv(firstNumber, secondNumber);
//    result2 = modResult(firstNumber, secondNumber);
//    assert(-142 == toInt(result));
//    assert(6 == toInt(result2));
//    clear(firstNumber);
//    clear(secondNumber);
//    clear(result);
//};
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
    assistTest();
    constructAndToStringTest();
    moduleSumTest();
    moduleDiffTest();
//    newBigInt *bigNum = constructBigIntFromInt(123456789);
//    printBigInt(bigNum);
//    printf("%s\n",bigIntToString(bigNum));
//    printf("%d",bigIntToInt(bigNum));

//    plusMinusTests();
//    multiplicationTests();
//    divAndModTest();
    return 0;
}