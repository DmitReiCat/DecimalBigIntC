#include <stdio.h>
#include "bigInt.h"



int main() {
    bigInt *number1 = constructBigInt("+554");
    bigInt *number2 = constructBigInt("-500");
    bigInt *sum = add(number1, number2);
    bigInt *diff = subtract(number1, number2);
    printBigInt(diff);
    bigInt *multiplication = multiply(number1, number2);
    bigInt *divRes = myDiv(number1, number2);
    printBigInt(divRes);
    bigInt  *modRes = modResult(number1, number2);
    printBigInt(modRes);
    int *str =
    return 0;
}
