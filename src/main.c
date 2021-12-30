#include <stdio.h>
#include "../include/bigInt.h"



int main(int argc, char *argv[]) {
    bigInt *firstNumber = constructBigInt("-6");
    bigInt *secondNumber = constructBigInt("79");
    printStats(firstNumber);
    printStats(secondNumber);

    bigInt *result = plus(firstNumber, secondNumber);
    printf("%d\n", toInt(result));


    if (argc == 3) {
        char *input = argv[1];
        char *output = argv[2];
    }
    else if (argc > 4) {
        printf("Too many arguments supplied.\n");
    }
    else {
        printf("Two arguments expected.\n");
    }



    return 0;
}
