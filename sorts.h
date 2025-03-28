#ifndef SORTS_H
#define SORTS_H

void bubbleSort(int *array, int size);
void selectionSort(int *array, int size);
void insertionSort(int *array, int size);
void mergeWrapper(int *array, int size);
void quickWrapper(int *array, int size);
void sortWrapper(void (*f)(int *v, int s), int *array, int arraySize, char *string);

#endif