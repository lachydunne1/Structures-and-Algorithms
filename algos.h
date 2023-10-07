#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



// Sorting Algorithms
void bubble_sort(int* arr, int numsSize);
void ms_divide(sllist *list, sllist *secondhalf);
void merge(sllist *first, sllist *second, sllist *out);
void merge_sort(sllist *list);