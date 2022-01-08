#include <stdio.h>
#include "../include/bigIntAssist.h"

int myPow(int x,int n) {
    int i;
    int number = 1;
    for (i = 0; i < n; ++i)
        number *= x;

    return(number);
}

void printBigInt(newBigInt *this) {
    printf("BigInt= [");
    for (int i = 0; i < this->size; i++) {
        printf("%d,", *(this->numberPtr + i));
    }
    printf("_]\n");
};
