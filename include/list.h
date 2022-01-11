#ifndef UNTITLED_LIST_H
#define UNTITLED_LIST_H
typedef struct ListOfInt {
    int size;
    int *numberPtr;
} listOfInt;

listOfInt* constructEmptyList();
void listPrint(listOfInt *this);
void freeList(listOfInt *this);
void reverseList(listOfInt *this);
void listAppend(listOfInt *this, long long int item);
void listAddReversed(listOfInt *this, int position, long long int number);

#endif //UNTITLED_LIST_H
