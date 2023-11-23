#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <structures.h>


// Sorting Algorithms
void bubble_sort(int* arr, int numsSize);
void ms_divide(sllist *list, sllist *secondhalf);
void merge(sllist *first, sllist *second, sllist *out);
void merge_sort(sllist *list);
void insertion_sort(int* arr, int numsSize);


void matrix_zero(int16_t *matrix, uint8_t elements);
void matrix_print(int16_t *matrix, uint8_t *dim);
void matrix_sum(int16_t* m_A, uint8_t* size_M, int16_t*  m_B, int16_t* output);
void matrix_add(int16_t* m_A, uint8_t* size_A, int k, int16_t* output);
void matrix_scale(int16_t* m_A, uint8_t* size_A, int16_t k, int16_t* output);
void matrix_mul(uint16_t *A, uint8_t dims_A[], uint16_t *B, uint8_t dims_B[], uint16_t *result);