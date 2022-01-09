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
    printf("conversion testing...\n\n");

    int number = 0;
    while (number <= 100) {
        assertConstructInt(number);
        number++;
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

    printf("\nconversion testing successful!\n\n");
}


void assertModuleSumFromInt(int firstNumber, int secondNumber) {
    newBigInt *firstBigNum = constructBigIntFromInt(firstNumber);
    newBigInt *secondBigNum = constructBigIntFromInt(secondNumber);
    newBigInt *result = moduleAdd(firstBigNum, secondBigNum);
    printf("  //trying to %d + %d", firstNumber, secondNumber);
    assert(firstNumber + secondNumber == bigIntToInt(result));
    printf("  (yoshi!)\n");
    freeBigInt(firstBigNum);
    freeBigInt(secondBigNum);
    freeBigInt(result);
}


void moduleSumTest() {
    printf("moduleSum testing...\n\n");
    for (int firstNum = 100; firstNum <= 110; firstNum++) {
        assertModuleSumFromInt(firstNum, 31);
    }
    for (int firstNum = 1004567890; firstNum <= 1004567950; firstNum++) {
        assertModuleSumFromInt(firstNum, 1034567890);
    }
    for (int firstNum = 100000000; firstNum <= 100000010; firstNum++) {
        assertModuleSumFromInt(firstNum, 31);
    }

    // overflow test
    assertModuleSumFromInt(99999999, 1);

    // overflow test 2
    newBigInt *firstBigNum = constructBigIntFromStr("999999999999999999999999");
    newBigInt *secondBigNum = constructBigIntFromStr("999999999999999999999999");
    newBigInt *result = moduleAdd(firstBigNum, secondBigNum);
    printf("  //trying to %s", "999999999999999999999999 x2");
    int preRes = strcmp("+1999999999999999999999998", bigIntToString(result));
    assert(0 == preRes);
    printf("  (yoshi!)\n");
    freeBigInt(firstBigNum);
    freeBigInt(secondBigNum);
    freeBigInt(result);

    printf("\nmoduleSum testing successful!\n\n");
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
//    newBigInt *bigNum = constructBigIntFromInt(1234567899);
//    printBigInt(bigNum);




//    printf("test insertAndSetZeroBlock\n");
//    newBigInt *bigNum = constructBigIntFromStr("99999999999999999");
//    insertToZeroBlock(bigNum, 687);
//    printBigInt(bigNum);
//    printf("digitCount = %d\n", digitCount(0));
//    printf("digitCount = %d\n", digitCount(10));
//    printf("digitCount = %d\n", digitCount(20));
//    printf("digitCount = %d\n", digitCount(99));
//    printf("digitCount = %d\n", digitCount(999999));
//    free(bigNum);
}

int main() {
//    assistTest();
    constructAndToStringTest();
    moduleSumTest();
//    newBigInt *bigNum = constructBigIntFromInt(123456789);
//    printBigInt(bigNum);
//    printf("%s\n",bigIntToString(bigNum));
//    printf("%d",bigIntToInt(bigNum));

//    plusMinusTests();
//    multiplicationTests();
//    divAndModTest();
    return 0;
}