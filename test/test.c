#include <assert.h>
#include <stdio.h>
#include "../include/newBigInt.h"
#include "../include/bigIntAssist.h"
#include <string.h>



void assertConstructInt(int number) {
    bigInt *bigNum = constructBigIntFromInt(number);
    assert(number == bigIntToInt(bigNum));
    printf("  //success on converting %d\n", number);

    freeBigInt(bigNum);
}

void assertConstructStr(char number[]) {
    bigInt *bigNum = constructBigIntFromStr(number);
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
    bigInt *firstBigNum = constructBigIntFromInt(firstNumber);
    bigInt *secondBigNum = constructBigIntFromInt(secondNumber);
    bigInt *result = moduleUnited(firstBigNum, secondBigNum, true);
    printf("  //trying to %d + %d", firstNumber, secondNumber);
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
    bigInt *firstBigNum = constructBigIntFromStr("999999999999999999999999");
    bigInt *secondBigNum = constructBigIntFromStr("999999999999999999999999");
    bigInt *result = moduleUnited(firstBigNum, secondBigNum, true);
    printf("  //trying to %s", "999999999999999999999999 x2");
    printBigInt(result);
    printf("size= %d, digitCount= %d\n", result->size, result->digitCount);
    int preRes = strcmp("+1999999999999999999999998", bigIntToString(result));
    assert(0 == preRes);
    printf("  (yoshi!)\n");

    freeBigInt(result);
    freeBigInt(firstBigNum);
    freeBigInt(secondBigNum);

    printf("moduleSum testing successful!\n\n");
}

void assertModuleDiffFromInt(int firstNumber, int secondNumber) {
    bigInt *firstBigNum = constructBigIntFromInt(firstNumber);
    bigInt *secondBigNum = constructBigIntFromInt(secondNumber);
    bigInt *result = moduleUnited(firstBigNum, secondBigNum, false);
    printf("  //trying to %d - %d", firstNumber, secondNumber);
    assert(firstNumber - secondNumber == bigIntToInt(result));
    printf("  (yoshi!)\n");

    freeBigInt(firstBigNum);
    freeBigInt(secondBigNum);
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
    bigInt *firstBigNum = constructBigIntFromInt(firstNumber);
    bigInt *secondBigNum = constructBigIntFromInt(secondNumber);
    bigInt *result = plus(firstBigNum, secondBigNum);
    printf("  //trying to %d + %d", firstNumber, secondNumber);
    assert(firstNumber + secondNumber == bigIntToInt(result));
    printf("  (yoshi!)\n");

    freeBigInt(firstBigNum);
    freeBigInt(secondBigNum);
    freeBigInt(result);
}

void assertMinusFromInt(int firstNumber, int secondNumber) {
    bigInt *firstBigNum = constructBigIntFromInt(firstNumber);
    bigInt *secondBigNum = constructBigIntFromInt(secondNumber);
    bigInt *result = minus(firstBigNum, secondBigNum);
    printf("  //trying to %d - %d", firstNumber, secondNumber);
    assert(firstNumber - secondNumber == bigIntToInt(result));
    printf("  (yoshi!)\n");

    freeBigInt(firstBigNum);
    freeBigInt(secondBigNum);
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
    bigInt *firstBigNum = constructBigIntFromInt(firstNumber);
    bigInt *secondBigNum = constructBigIntFromInt(secondNumber);
    bigInt *result = multiplyBigInts(firstBigNum, secondBigNum);
    printf("  //trying to %d * %d", firstNumber, secondNumber);
    assert(firstNumber * secondNumber == bigIntToInt(result));
    printf("  (yoshi!)\n");

    freeBigInt(firstBigNum);
    freeBigInt(secondBigNum);
    freeBigInt(result);
}

void assertMultiplicationFromString(char firstNumber[], char secondNumber[], char resultString[]) {
    bigInt *firstBigNum = constructBigIntFromStr(firstNumber);
    bigInt *secondBigNum = constructBigIntFromStr(secondNumber);
    bigInt *result = multiplyBigInts(firstBigNum, secondBigNum);
    printf("  //trying to %s * %s", firstNumber, secondNumber);
    int preRes = strcmp(resultString, bigIntToString(result));
    assert(0 == preRes);
    printf("  (yoshi!)\n");

    freeBigInt(firstBigNum);
    freeBigInt(secondBigNum);
    freeBigInt(result);
}

void multiplicationTests() {
    printf("multiplication testing...\n");

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
    printf("multiplication testing successful!\n\n");
}

void assertCompareTests(int firstNumber, int secondNumber) {
    bigInt *firstBigNum = constructBigIntFromInt(firstNumber);
    bigInt *secondBigNum = constructBigIntFromInt(secondNumber);
    int res = compareTo(firstBigNum, secondBigNum, false);
    int preRes;
    if (firstNumber > secondNumber) preRes = 1;
    else if (firstNumber == secondNumber) preRes = 0;
    else preRes = -1;
    printf("  //comparing %d to %d", firstNumber, secondNumber);
    assert(preRes == res);
    printf("  (yoshi!)\n");
    freeBigInt(firstBigNum);
    freeBigInt(secondBigNum);
}

void compareTests() {
    printf("compare testing...\n");

    assertCompareTests(500000000, 50);
    assertCompareTests(50, 50);
    assertCompareTests(500, 50);
    assertCompareTests(500, 50000);
    assertCompareTests(500, -50000);
    assertCompareTests(-500, 50000);
    assertCompareTests(-500, -50000);

    printf("compare testing successful!\n\n");
}

void assertDivisionOnlyRemains(int firstNumber, int secondNumber) {
    bigInt *firstBigNum = constructBigIntFromInt(firstNumber);
    bigInt *secondBigNum = constructBigIntFromInt(secondNumber);
    bigInt *result = bigIntMod(firstBigNum, secondBigNum);
    printf("  //trying to %d mod %d", firstNumber, secondNumber);
    assert(firstNumber % secondNumber == bigIntToInt(result));
    printf("  (yoshi!)\n");

    freeBigInt(firstBigNum);
    freeBigInt(secondBigNum);
    freeBigInt(result);
}

void assertDivisionOnlyRemainsFalse(int firstNumber, int secondNumber) {
    bigInt *firstBigNum = constructBigIntFromInt(firstNumber);
    bigInt *secondBigNum = constructBigIntFromInt(secondNumber);
    bigInt *result = bigIntDiv(firstBigNum, secondBigNum);
    printf("  //trying to %d div %d", firstNumber, secondNumber);
    assert(firstNumber / secondNumber == bigIntToInt(result));
    printf("  (yoshi!)\n");

    freeBigInt(firstBigNum);
    freeBigInt(secondBigNum);
    freeBigInt(result);
}


void divisionTests() {
    printf("division testing...\n");
    for (int number = 1; number <= 1000000000; number *= 10) {
        assertDivisionOnlyRemains(number, -10);
    }
    for (int number = 1; number <= 1000000000; number *= 10) {
        assertDivisionOnlyRemains(-1000, number);
    }
    for (int number = 1; number <= 1000000000; number *= 10) {
        assertDivisionOnlyRemainsFalse(number, -10);
    }
    for (int number = 1; number <= 1000000000; number *= 10) {
        assertDivisionOnlyRemainsFalse(-1000, number);
    }
    assertDivisionOnlyRemains(934275, 3289);
    assertDivisionOnlyRemainsFalse(934275, 3289);


    printf("division testing successful\n");
}


void assistTest() {
    bigInt *bigNum = constructBigIntFromStr("1");
    printBigInt(bigNum);
    deleteExtraZeroBlocks(bigNum);
    printBigInt(bigNum);
    freeBigInt(bigNum);
}


int main() {
    listOfInt *testList = constructEmptyList();
    listAddReversed(testList,0,1000000000);
    listAddReversed(testList,1,20);
    reverseList(testList);
    listPrint(testList);

    assistTest();
    constructAndToStringTest();
    moduleSumTest();
    moduleDiffTest();
    plusMinusTests();
    multiplicationTests();
    compareTests();
    divisionTests();
    return 0;
}