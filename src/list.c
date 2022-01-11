#include "../include/list.h"
#include <stdio.h>
#include <stdlib.h>
#include "../include/consts.h"
listOfInt* constructEmptyList() {
    listOfInt *resList = NULL; resList = (listOfInt*)malloc(sizeof(listOfInt));
    resList->numberPtr = NULL;
    resList->size = 0;
    return resList;
}

void listPrint(listOfInt *this) {
    printf("\n listOf int= [");
    for (int i = 0; i < this->size; i++) {
        printf("%d,", this->numberPtr[i]);
    }
    printf("_]\n");
}

void freeList(listOfInt *this) {
    free(this->numberPtr);
    free(this);
}

void reverseList(listOfInt *this) {
    int start = 0;
    int end = this->size - 1;
    int temp;
    while (start < end) {
        temp = this->numberPtr[start];
        this->numberPtr[start] = this->numberPtr[end];
        this->numberPtr[end] = temp;
        start++;
        end--;
    }
}

void listAppend(listOfInt *this, long long int item) {
    this->size += 1;
    this->numberPtr = realloc(this->numberPtr, (this->size) * sizeof(int));
    if (item < WORD_LENGTH) this->numberPtr[this->size - 1] = (int)item;
    else {
        this->numberPtr[this->size - 1] = (int)(item % WORD_LENGTH);
        listAppend(this, item / WORD_LENGTH);
    }
}

void listAddReversed(listOfInt *this, int position, long long int number) {
    if (position < this->size) {
        int listDigit = this->numberPtr[position];
        if (listDigit + number < WORD_LENGTH) this->numberPtr[position] += (int)number;
        else {
            this->numberPtr[position] = (int)((listDigit + number) % WORD_LENGTH);
            listAddReversed(this, position + 1, (listDigit + number) / WORD_LENGTH);
        }
    } else {
        listAppend(this, number);
    }
}