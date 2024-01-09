#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "structures.h"

/*

*/

/*
    Sort Algorithms:
    bubble_sort: takes a pointer to an array, and size of the array as
    arugments and sorts them O(n^2), Ohm(n)

    insertion_sort: insertion sort is an effective algorithm for sorting small 
    arrays.

    merge_sort: defined with multiple functions to support, such as divide
    and merge. Requires a sllist to be created, each entry of which contains a key.
    After using the entries of sllist will be rearranged so that the keys in all the entries 
    are sorted in non-decreasing order.

*/

void bubble_sort_int(int* arr,int  size) 
{
    int i, j , temp;
    for (i = 0; i < size - 1; i++){ // initial loop
        for (j = 0; j < size - i - 1; j++){ // initial loop conditon for bubble sort
            if ( arr[j] > arr[j + 1]) {
                // swapping the elements
                temp = arr[j]; 
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

}

void bubble_sort_float(double* arr, int size)
{
    int i, j;
    double temp; 
    for (i = 0; i< size -1; i++){
        for (j=0; j<size - j - 1; j++){
            if ( arr[j] > arr[j+1]){
                    temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
            }
        }

    }
}

void insertion_sort_int(int* arr, int numsSize){

   int key, j;
   for (int i = 1; i < numsSize; i++){
        key = arr[i];
        j = i -1;
        //Move elements of arr[0...i-1], that are greater than key
        //to one position ahead of their current position.
        while((j>=0) && arr[j] > key){
            arr[j+1] = arr[j];
            j = j - 1;
        }
        arr[j+1] = key;
   }
}

void insertion_sort_float(double* arr, int size){

    int i, j;
    double key;

    for (i = 1; i<size; i++){

        key = arr[i];
        j = i-1;

        while((j>=0) && arr[j] > key){
            arr[j+1] = arr[j];
            j = j - 1;
        }
        arr[j+1] = key;

    }
}



void ms_divide(sllist *list, sllist *secondhalf)
{
    sllnode *current, *midpoint;
    //check if list is empty
    if((midpoint = list->head) == NULL){
        secondhalf->head = NULL; //if empty, set second half to NULL
        }else{
            current  = midpoint -> next; // initalize current as sllnode pointer
            // Traverse the list to find the midpoint
            while (current){
                current = current -> next; //move current one step
                if (current){
                midpoint =midpoint -> next; //move midpoint one step for every two steps of current
                current = current -> next; // move current another step
            }
        }
        // split the list into two halve
        secondhalf->head = midpoint->next; //set the head of the second half
        midpoint->next = NULL; //terminate the first half
        }
}

void merge(sllist *first, sllist *second, sllist *out) {
    sllnode *p1, *p2; // pointers to traverse first and second lists
    sllnode *lastsorted = NULL; // always points to the last node of sorted list

    // Check if either list is empty
    if (!first->head) {
        *out = *second;
        return;
    } else if (!second->head) {
        *out = *first;
        return;
    }

    p1 = first->head; // initialize pointers to the heads of the lists
    p2 = second->head;

    // Determine the head of the merged list
    if (p1->val < p2->val) {
        out->head = p1;
        p1 = p1->next;
    } else {
        out->head = p2;
        p2 = p2->next;
    }

    lastsorted = out->head; // initialize lastsorted to the head of the merged list

    // Merge the lists by comparing values and linking nodes
    while (p1 && p2) {
        if (p1->val < p2->val) {
            lastsorted->next = p1;
            p1 = p1->next;
        } else {
            lastsorted->next = p2;
            p2 = p2->next;
        }
        lastsorted = lastsorted->next; // move lastsorted to the last node of the merged list
    }

    // If one list is longer, append the remaining nodes to the merged list
    if (p1) {
        lastsorted->next = p1;
    } else {
        lastsorted->next = p2;
    }
}


void merge_sort(sllist *list) {
    if (get_sll_length(list->head) <= 1) { // check if list is indivisible
        return; // base case: if list has 1 or 0 elements, it's already sorted
    }

    sllist firsthalf = {0, list->head}; // create first half list
    sllist secondhalf = {0, NULL}; // create second half list

    ms_divide(&firsthalf, &secondhalf); // divide the list in half

    merge_sort(&firsthalf); // recursively sort the first half
    merge_sort(&secondhalf); // recursively sort the second half

    merge(&firsthalf, &secondhalf, list); // merge the sorted halves back into the original list
}



/*
    Matrix Operations: All matrix operations defined below will convert matrices into 1D
    in order to compute the desired outcome.
*/


// brief: set all matrix elements to 0.
void matrix_zero(int16_t *matrix, uint8_t elements){

    for (uint8_t i = 0; i < elements; i++){
        //derefence matrix pointer, and iterate through matrix using pointer 
        //arithmetic
        *(matrix+i) = 0;
    }
}

//brief: use indexing to print all elements of a two-dimensional array.
void matrix_print(int16_t *matrix, uint8_t *dim){
    for (uint8_t i = 0; i<dim[0]; i++){

        for (uint8_t j = 0; j<dim[1]; j++){
            printf("% 6d ", matrix[i * dim[1] + j]);
        }
        printf("\n");
    }
}

//brief: calculate matrix dimensions and sum elements. elements must be of the 
//same dimensions. Can also use indexing here, may be useful to do so for consistency.
void matrix_sum(int16_t* m_A, uint8_t* size_M, int16_t*  m_B, int16_t* output){

    for (uint8_t i = 0; i<(size_M[0] * size_M[1]); i++)
        output[i] = m_B[i] + m_A[i];
    
}


void matrix_add(int16_t* m_A, uint8_t* size_A, int k, int16_t* output){

    for(uint8_t i = 0; i<(size_A[0]*size_A[1]); i++)
        output[i] = m_A[i] + k;
}

void matrix_scale(int16_t* m_A, uint8_t* size_A, int16_t k, int16_t* output){

    for(uint8_t i = 0; i<(m_A[0] * m_A[1]); i++)
        output[i] = m_A[i] * k;

}

void matrix_mul(uint16_t *A, uint8_t dims_A[], uint16_t *B, uint8_t dims_B[], uint16_t *result){
    uint8_t rA = dims_A[0];
    uint8_t cA  = dims_A[1];
    uint8_t cB = dims_B[1];

    
    for (uint8_t i = 0; i < rA; i++) {
        for (uint8_t j = 0; j < cA; j++) {

            //initialize element as zero
            *(result + i * cB + j) = 0;
            for (uint8_t k = 0; k < cA; k++) {
                //use indexing to dereference pointers to element as dot product value.
                *(result + i * cB + j) += (*(A + i *  + k)) * (*(B + k * cB+ j));
            }
        }

    }
}

