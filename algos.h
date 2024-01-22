#ifndef algos_h
#define algos_h

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "structures.h"

// Sorting Algorithms
void bubble_sort_int(int* arr, int size);
void bubble_sort_float(double* arr, int size);

void ms_divide(sllist *list, sllist *secondhalf);

void merge(sllist *first, sllist *second, sllist *out);
void merge_sort(sllist *list);

void insertion_sort_int(int* arr, int size);
void insertion_sort_float(double* arr, int size);

#endif //algos_h