#include <assert.h>
#include <corecrt_malloc.h>
#include <stdio.h>
#include "../include/bigInt.h"
#include <string.h>
void plusMinusTests() {
    bigInt *firstNumber = constructBigInt("-690");
    bigInt *secondNumber = constructBigInt("-79");
    bigInt *result = plus(firstNumber, secondNumber);

    assert(-769 == toInt(result));
    clear(secondNumber);
    clear(result);

    secondNumber = constructBigInt("79");
    result = plus(firstNumber, secondNumber);
    assert(-611 == toInt(result));
    clear(firstNumber);
    clear(secondNumber);
    clear(result);

    firstNumber = constructBigInt("10");
    secondNumber = constructBigInt("-10");
    result = plus(firstNumber, secondNumber);
    int preRes = strcmp("+0", toString(result));
    assert(0 == preRes);
    clear(firstNumber);
    clear(secondNumber);
    clear(result);


}

void multiplicationTests() {
    bigInt *firstNumber = constructBigInt("-5");
    bigInt *secondNumber = constructBigInt("91");
    bigInt *result = multiply(firstNumber, secondNumber);
    assert(-455 == toInt(result));
    clear(firstNumber);
    clear(secondNumber);
    clear(result);


    firstNumber = constructBigInt("-5545");
    secondNumber = constructBigInt("9000001");
    result = multiply(firstNumber, secondNumber);
    int preRes = strcmp("-49905005545", toString(result));
    assert(0 == preRes);
    clear(firstNumber);
    clear(secondNumber);
    clear(result);


    firstNumber = constructBigInt("-1000");
    secondNumber = constructBigInt("9");
    result = multiply(firstNumber, secondNumber);
    preRes = strcmp("-9000", toString(result));
    assert(0 == preRes);
    clear(firstNumber);
    clear(secondNumber);
    clear(result);

}

void divAndModTest() {
    bigInt *firstNumber = constructBigInt("-91");
    bigInt *secondNumber = constructBigInt("5");
    bigInt *result = myDiv(firstNumber, secondNumber);
    bigInt *result2 = modResult(firstNumber, secondNumber);

    assert(-18 == toInt(result));
    assert(1 == toInt(result2));
    clear(firstNumber);
    clear(secondNumber);
    clear(result);
    clear(result2);

    firstNumber = constructBigInt("-10000");
    secondNumber = constructBigInt("200");
    result = myDiv(firstNumber, secondNumber);
    assert(-50 == toInt(result));
    result2 = modResult(firstNumber, secondNumber);
    assert(0 == toInt(result2));
    clear(firstNumber);
    clear(secondNumber);
    clear(result);
    clear(result2);

    firstNumber = constructBigInt("1000");
    secondNumber = constructBigInt("-7");
    result = myDiv(firstNumber, secondNumber);
    result2 = modResult(firstNumber, secondNumber);
    assert(-142 == toInt(result));
    assert(6 == toInt(result2));
    clear(firstNumber);
    clear(secondNumber);
    clear(result);
};


int main() {
    plusMinusTests();
    multiplicationTests();
    divAndModTest();
    return 0;
}