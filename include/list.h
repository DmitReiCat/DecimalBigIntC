#ifndef UNTITLED_LIST_H
#define UNTITLED_LIST_H
typedef struct ListOfInt {
    int size;
    int *numberPtr;
} listOfInt;

listOfInt* constructEmptyList();
void listAppend(listOfInt *this, int item);
void  listPrint(listOfInt *this);
void freeList(listOfInt *this);
void reverseList(listOfInt *this);
void listAddReversed(listOfInt *this, int position, int number);
void removeZerosFromEnd(listOfInt *this);

#endif //UNTITLED_LIST_H
