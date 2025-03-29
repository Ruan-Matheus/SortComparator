# SortComparator

## Overview

The **SortComparator** program is a C-based utility designed to compare the performance of various sorting algorithms. It allows users to sort arrays of integers using different algorithms and measure the time taken by each algorithm. The program supports both randomly generated arrays and arrays read from standard input.

## Features

- Supports multiple sorting algorithms:
  - Bubble Sort
  - Selection Sort
  - Insertion Sort
  - Merge Sort
  - Quick Sort
- Measures and displays the time taken by each sorting algorithm.
- Allows sorting of arrays provided via standard input or randomly generated arrays.
- Provides options to sort all algorithms at once or selectively choose specific algorithms.
- Optionally prints the sorted array.

## Usage

The program accepts the following command-line options:

| Option | Description                                                                 |
|--------|-----------------------------------------------------------------------------|
| `-p`   | Print the sorted array after sorting.                                       |
| `-a`   | Sort the array using all available algorithms.                              |
| `-b`   | Sort the array using **Bubble Sort**.                                       |
| `-m`   | Sort the array using **Merge Sort**.                                        |
| `-s`   | Sort the array using **Selection Sort**.                                    |
| `-i`   | Sort the array using **Insertion Sort**.                                    |
| `-q`   | Sort the array using **Quick Sort**.                                        |
| `-n`   | Generate a random array of integers. Requires an additional argument for the size of the array. |

### Examples

1. **Sort using all algorithms with a random array of size 100:**

   ```bash
   ./sortings_comparission -a -n 100
   ```

2. **Sort using Bubble Sort and print the sorted array:**

   ```bash
   ./sortings_comparission -bp
   ```

3. **Sort using Merge Sort with numbers read from standard input:**

   ```bash
   ./sortings_comparission -m
   ```

4. **Generate a random array of size 50 and sort using Quick Sort:**

   ```bash
   ./sortings_comparission -qn 50
   ```

### Notes

- If the `-n` option is not provided, the program expects numbers to be provided via standard input.
- The `-a` option enables all sorting algorithms, overriding individual algorithm flags (`-b`, `-m`, `-s`, `-i`, `-q`).
- The program outputs the time taken by each sorting algorithm in seconds.

### TODO

- Add a flag to generate arrays that are already sorted or inversely sorted for testing edge cases.
