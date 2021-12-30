#include <stdio.h>
#include "bigInt.h"



int main() {
    bigInt *number1 = constructBigInt("+550");
    bigInt *number2 = constructBigInt("+500");
    bigInt *sum = plus(number1, number2);
    bigInt *diff = minus(number1, number2);
    bigInt *multiplication = multiply(number1, number2);
    bigInt *divRes = myDiv(number1, number2);
    bigInt *modRes = modResult(number1, number2);
    printf("%d\n", toInt(multiplication));
    printf("%s\n", toString(multiplication));
    return 0;
}
