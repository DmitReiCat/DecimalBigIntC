#include <stdio.h>
//#include "../include/bigInt.h"
#include "../include/newBigInt.h"
#include "../include/bigIntAssist.h"


int main(int argc, char *argv[]) {
//    bigInt *firstNumber = constructBigIntFromStr("-6");
//    bigInt *secondNumber = constructBigIntFromStr("79");
//    printStats(firstNumber);
//    printStats(secondNumber);
    newBigInt *firstNumber = constructBigIntFromStr("-1234567890987654321");
//    for (int firstNumber = 0; firstNumber <= 10000; firstNumber++) {
////        bigInt firstBigInt =
//        printf("%s\n", (char*)firstNumber);
//
//
//
//    }


    newBigInt *secondNumber = constructBigIntFromStr("0");
    printf("%s\n", bigIntToString(firstNumber));
    printf("%s\n", bigIntToString(secondNumber));
    printBigInt(firstNumber);
    printBigInt(secondNumber);



//
//    bigInt *result = plus(firstNumber, secondNumber);
//    printf("%d\n", toInt(result));
//
//
//    if (argc == 3) {
//        char *input = argv[1];
//        char *output = argv[2];
//    }
//    else if (argc > 4) {
//        printf("Too many arguments supplied.\n");
//    }
//    else {
//        printf("Two arguments expected.\n");
//    }



    return 0;
}
