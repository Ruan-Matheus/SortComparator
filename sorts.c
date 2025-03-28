#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "sorts.h"
#include <string.h>

extern int optind;

void printArray(int *array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}


void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


void sortWrapper(void (*f)(int *v, int s), int *array, int arraySize, char *sortName) {

    int *arrayCopy = malloc(arraySize * sizeof(int));
    if (!arrayCopy) {
        fprintf(stderr, "Failed to allocate memory for the copy array\n");
        return;
    }

    for (int i = 0; i < arraySize; i++) {
        arrayCopy[i] = array[i];
    }

    clock_t start = clock();
    (*f)(arrayCopy, arraySize);

    double timeTaken = ((double)(clock() - start)) / CLOCKS_PER_SEC;
    // Calculate the number of dashes needed
    int nameLength = strlen(sortName);
    int totalWidth = 40; // Adjust this based on desired total length
    int numDashes = totalWidth - nameLength;

    // Print the name, dashes, and time
    printf("%s ", sortName);
    for (int i = 0; i < numDashes; i++) {
        printf("-");
    }
    printf(" Time taken: %lf secs.\n", timeTaken);

    free(arrayCopy);
}


void bubbleSort(int *array, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (array[j] > array[j+1]) {
                swap(&array[j], &array[j+1]);
            }
        }
    }
}


void selectionSort(int *array, int size) {
    for (int i = 0; i < size - 1; i++) {
        int posMenor = i;
        for (int j = i + 1; j < size; j++) {
            if (array[j] < array[posMenor]) {
                posMenor = j;
            }
        }
        if (i != posMenor) {
            swap(&array[i], &array[posMenor]);
        }
    }
}


void insertionSort(int *array, int size) {
    int i, aux, j;
    for (i = 1; i < size; i++) {
        aux = array[i];
        j = i;
        while ((j > 0) && (aux < array[j-1])) {
            array[j] = array[j-1];
            j--;
        }
        array[j] = aux;
    }
}


void merge(int *array, int start, int mid, int end) {

    int i, j, k;
    int sizeSeq1 = mid - start + 1;
    int sizeSeq2 = end - mid;

    int seq1[sizeSeq1];
    for (i = 0; i < sizeSeq1; i++) {
        seq1[i] = array[start+i];
    }

    int seq2[sizeSeq2];
    for (j = 0; j < sizeSeq2; j++) {
        seq2[j] = array[mid+j+1];
    }

    k = start, i = 0, j = 0;

    while ((i < sizeSeq1) && (j < sizeSeq2)) {
        if (seq1[i] <= seq2[j]) {
            array[k] = seq1[i];
            i++;
        }
        else {
            array[k] = seq2[j];
            j++;
        }
        k++;
    }

    while (i < sizeSeq1) {
        array[k++] = seq1[i++];
    }

    while (j < sizeSeq2) {
        array[k++] = seq2[j++];
    } 
}


void mergeSort(int *array, int start, int end) {
    if (start >= end) {
        return;
    }

    int mid = (start + end) / 2;

    mergeSort(array, start, mid);
    mergeSort(array, mid + 1, end);
    merge(array, start, mid, end);
}


int partition(int *array, int low, int high) {
    int pivot = array[low];
    int i = low;
    int j = high;

    while (i < j) {
        do {
            i++;
        } while (array[i] <= pivot);

        do {
            j--;
        } while (array[j] > pivot);

        if (i < j) {
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[low], &array[j]);
    return j;
}



void quickSort(int *array, int low, int high) {
    if (low >= high) {
        return;
    }
    int j = partition(array, low, high);
    quickSort(array, low, j);
    quickSort(array, j+1, high);
}


void mergeWrapper(int *array, int size) {
    mergeSort(array, 0, size - 1);
}


void quickWrapper(int *array, int size) {
    quickSort(array, 0, size);
}