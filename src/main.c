#include <stdio.h>
#include <stdlib.h>
#include "../include/newBigInt.h"
#include "../include/bigIntAssist.h"

void sum(char *ipath, char *opath) {
    FILE *ifptr;
    FILE *ofptr;


    if ((ifptr = fopen(ipath, "r")) == NULL){
        printf("Error! opening file");
        exit(1);
    }
    if ((ofptr = fopen(opath, "w")) == NULL){
        printf("Error! opening file");
        exit(1);
    }

    bigInt *sumRes = constructBigIntFromInt(0);
    while (!feof(ifptr)) {
        int number;
        fscanf(ifptr, "%d", &number);
        bigInt *bigNum = constructBigIntFromInt(number);
        sumRes = plus(sumRes, bigNum, true);
    }

    printf("\n sumRes= %s", bigIntToString(sumRes));
    fprintf(ofptr, "%s", bigIntToString(sumRes));
    freeBigInt(sumRes);
    fclose(ifptr);
    fclose(ofptr);
}


int main(int argc, char *argv[]) {
    if (argc == 3) {
        printf("summing..");
        char *input = argv[1];
        char *output = argv[2];
        sum(input, output);
    }
    else if (argc > 4) {
        printf("Too many arguments supplied.\n");
    }
    else {
        printf("Two arguments expected.\n");
    }
    return 0;
}
