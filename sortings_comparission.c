#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#define INITIAL_SIZE 10
#define CHUNCK_SIZE 10


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


int main(int argc, char **argv) {

    srand(time(NULL));

    bool toBubble = false;
    bool toMerge = false;
    bool toSelection = false;
    bool toInsertion = false;
    bool toQuick = false;

    bool readNumbers = true;
    bool printSortedArray = false;
    int opt;

    while ((opt = getopt(argc, argv, "pbmsiqn")) != -1) {
        switch(opt) {
            case 'p':
                printSortedArray = true;
                break;
            case 'b':
                toBubble = true;
                break;
            case 'm':
                toMerge = true;
                break;
            case 's':
                toSelection = true;
                break;
            case 'i':
                toInsertion = true;
                break;
            case 'q':
                toQuick = true;
                break;
            case 'n':
                readNumbers = false;
                break;
            default:
                fprintf(stderr, "Usage: %s [-p -m -n <number (only if -n is used)>] [file...]\n", argv[0]);
                exit(EXIT_FAILURE);

        }
    }
    // Now optind (declared extern int by <unistd.h>) is the index of the first non-option argument.

    int *array = NULL;
    int arraySize = 0;

    // If the `-n` option is provided, read the size from the command line
    if (!readNumbers) {
        // The flag for the array size was setted but no size was guiven. It is Important to check if optind is within the bounds of the array
        if ((optind >= argc) || ((argv[optind]) == NULL)) {
            fprintf(stderr, "Size of the arrays was not guiven.\n");
            fprintf(stderr, "Usage: %s [-m -n <number (only if -n is used)>] [file...]\n", argv[0]);  
            return -1;
        }

        
        arraySize = atoi(argv[optind]);
        if (arraySize <= 0) {
            fprintf(stderr, "Usage: %s [-m -n <number (only if -n is used)>] [file...]\n", argv[0]);
            return -1;
        }

        array = malloc(arraySize * sizeof(int));
        if (!array) {
            fprintf(stderr, "Failed to allocate memory");
            return -1;
        }

        // Generate random numbers
        for (int i = 0; i < arraySize; i++) {
            array[i] = rand() % arraySize; 
        }
    }
    

    // Otherwise, read numbers from stdin
    else {
        int numElements = 0;
        arraySize = INITIAL_SIZE;
        array = malloc(arraySize * sizeof(int));

        
        if (!array) {
            fprintf(stderr, "Failed to allocate memory\n");
            return -1;
        }

        while (((scanf("%d", &array[numElements])) == 1) && !feof(stdin)) {
            numElements++;
            if (numElements >= arraySize) {
                arraySize += CHUNCK_SIZE;
                array = realloc(array, arraySize * sizeof(int));
                if (!array) {
                    fprintf(stderr, "Failed to reallocate memory\n");
                    return -1;
                }
            }
        }

        arraySize = numElements;
        array = realloc(array, arraySize * sizeof(int));
        if (!array) {
            fprintf(stderr, "Failed to resize the array\n");
            return -1;
        }
    }


    clock_t start, end;
    double timeTaken;
    
    if (toMerge) {
        
        int *arrayCopy = malloc(arraySize * sizeof(int));
        if (!arrayCopy) {
            fprintf(stderr, "Failed to allocate memory for the copy array\n");
            return -1;
        }

        for (int i = 0; i < arraySize; i++) {
            arrayCopy[i] = array[i];
        } 

        start = clock();
        mergeSort(arrayCopy, 0, arraySize - 1);
        end = clock();
        
        timeTaken = ((double)(end-start)) / CLOCKS_PER_SEC;
        printf("# Merge Sort --- Time taken: %lf secs\n", timeTaken);

        free(arrayCopy);
    }

    if (toSelection) {

        int *arrayCopy = malloc(arraySize * sizeof(int));
        if (!arrayCopy) {
            fprintf(stderr, "Failed to allocate memory for the copy array\n");
            return -1;
        }

        for (int i = 0; i < arraySize; i++) {
            arrayCopy[i] = array[i]; 
        }     

        start = clock();
        selectionSort(arrayCopy, arraySize);
        end = clock();
        
        timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("# Selection Sort --- Time taken: %lf secs\n", timeTaken);

        free(arrayCopy);
    }

    if (toInsertion) {

        int *arrayCopy = malloc(arraySize * sizeof(int));
        if (!arrayCopy) {
            fprintf(stderr, "Failed to allocate memory for the copy array\n");
            return -1;
        }

        for (int i = 0; i < arraySize; i++) {
            arrayCopy[i] = array[i];
        }

        start = clock();
        insertionSort(arrayCopy, arraySize);
        end = clock();

        timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("# Insertion Sort --- Time taken: %lf secs\n", timeTaken);

        free(arrayCopy);
    }

    if (toQuick) {

        int *arrayCopy = malloc(arraySize * sizeof(int));
        if (!arrayCopy) {
            fprintf(stderr, "Failed to allocate memory for the copy array\n");
            return -1;
        }

        for (int i = 0; i < arraySize; i++) {
            arrayCopy[i] = array[i];
        }

        start = clock();
        quickSort(arrayCopy, 0, arraySize);
        end = clock();

        timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("# Quick Sort --- Time taken: %lf secs\n", timeTaken);

        free(arrayCopy);
    }


    if (toBubble) {
        start = clock();
        bubbleSort(array, arraySize);
        end = clock();
        
        timeTaken = ((double)(end-start)) / CLOCKS_PER_SEC;
        printf("# Bubble Sort --- Time taken: %lf secs\n", timeTaken);

        if (printSortedArray) {
            printArray(array, arraySize);
        }

        free(array);
    }
    return 0;
}


// TODO: ADD A FLAG TO CREATE ARRAYS ALREADY SORTED OR INVERSED SORTED