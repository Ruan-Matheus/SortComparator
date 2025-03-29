#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include "sorts.h"

#define INITIAL_SIZE 10
#define CHUNCK_SIZE 10

extern int optind;

int main(int argc, char **argv) {

    srand(time(NULL));

    bool toBubble = false;
    bool toMerge = false;
    bool toSelection = false;
    bool toInsertion = false;
    bool toQuick = false;
    bool sortAll = false;

    bool readNumbers = true;
    bool printSortedArray = false;
    int opt;

    while ((opt = getopt(argc, argv, "pabmsiqn")) != -1) {
        switch(opt) {
            case 'p':
                printSortedArray = true;
                break;
            case 'a':
                sortAll = true;
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
    if (sortAll) {
        toBubble = true;
        toMerge = true;
        toSelection = true;
        toInsertion = true;
        toQuick = true;
        sortAll = true;
    }


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
    

    if (toBubble) {
        sortWrapper(&bubbleSort, array, arraySize, "Bubble Sort");
    }

    if (toSelection) {
        sortWrapper(&selectionSort, array, arraySize, "Selection Sort");
    }

    if (toInsertion) {
        sortWrapper(&insertionSort, array, arraySize, "Insertion Sort");
    }

    if (toMerge) {
        sortWrapper(&mergeWrapper, array, arraySize, "Merge Sort");
    }

    if (toQuick) {
        sortWrapper(&quickWrapper, array, arraySize, "Quick Sort");
    }
    
    free(array);

    return 0;
}


// TODO: ADD A FLAG TO CREATE ARRAYS ALREADY SORTED OR INVERSED SORTED
