#include "../include/list.h"
#include <stdio.h>
#include <stdlib.h>
listOfInt* constructEmptyList() {
    listOfInt *resList = NULL;
    resList = (listOfInt*)malloc(sizeof(listOfInt));
    resList->numberPtr = NULL;
    resList->size = 0;
    return resList;
}

void listAppend(listOfInt *this, int item) {
    this->size += 1;
    this->numberPtr = realloc(this->numberPtr, (this->size) * sizeof(int));
    if (item < 10) *(this->numberPtr + this->size - 1 ) = item;
    else {
        *(this->numberPtr + this->size - 1 ) = item % 10;
        listAppend(this, item / 10);
    }
}

void removeZerosFromEnd(listOfInt *this) {
    while (*(this->numberPtr + this->size - 1) == 0) {
        this->size--;
    }
    this->numberPtr = realloc(this->numberPtr, (this->size) * sizeof(int));
}

void listPrint(listOfInt *this) {
    printf("\n listOf int= [");
    for (int i = 0; i < this->size; i++) {
        printf("%d,", *(this->numberPtr + i));
    }
    printf("_]\n");
}

void freeList(listOfInt *this) {
    free(this->numberPtr);
    free(this);
}

/// ">" --> 1, "==" --> 0, "<" --> -1
int compareLists(listOfInt *this, listOfInt *other) {
    if (this->size > other->size ) return 1;
    else if (this->size < other->size) return -1;
    else {
        for (int index = this->size; index > 0; index--) {
            int thisDigit = *(this->numberPtr + this->size - 1);
            int otherDigit = *(other->numberPtr + other->size - 1);

            if (thisDigit > otherDigit) return 1;
            else if (thisDigit < otherDigit) return -1;
        }
    }
    return 0;
}

void reverseList(listOfInt *this) {
    int start = 0;
    int end = this->size - 1;
    int temp;
    while (start < end) {
        temp = *(this->numberPtr + start);
        *(this->numberPtr + start) = *(this->numberPtr + end);
        *(this->numberPtr + end) = temp;
        start++;
        end--;
    }
}

void listAddReversed(listOfInt *this, int position, int number) {
    if (position < this->size) {
        int listDigit = *(this->numberPtr + position);
        if (listDigit + number < 10) *(this->numberPtr + position) += number;
        else {
            int debug = (listDigit + number) % 10;
            *(this->numberPtr + position) = (listDigit + number) % 10;
            listAddReversed(this, position + 1, (listDigit + number) / 10);
        }
    } else {
        listAppend(this, number);
    }
}