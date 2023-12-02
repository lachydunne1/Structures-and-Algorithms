#ifndef structures_h
#define structures_h

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define HASH_LENGTH 45 // length of word in node (for hash tables)

// Hash Table
typedef struct hash_node {
    char word[HASH_LENGTH + 1];
    struct node *next;
} hash_node;

unsigned int size(void);
int32_t hash(const char *word);

// Singly Linked List
typedef struct sllnode {
    int val;
    struct sllnode* next;
} sllnode;

typedef struct sllist {
    int count;
    sllnode *head;
} sllist;

int get_sll_length(sllnode* head);
void clear_sll(sllist* seq);

// Stack
typedef struct stacknode {
    int value;
    struct stacknode* next;
} stacknode;

typedef struct {
    stacknode* top;
    int size;
} stack;

stack* create_stack();
int push(stack* stack, int value);
int pop(stack* stack);
int peek(stack* stack);
void stack_is_empty(stack* stack);
int stack_size(stack* stack);
void free_stack(stack* stack);

// Sorting Algorithms
void bubble_sort(int* arr, int numsSize);
void ms_divide(sllist *list, sllist *secondhalf);
void merge(sllist *first, sllist *second, sllist *out);
void merge_sort(sllist *list);

// Trees

typedef struct treenode{
    int value;
    struct treenode *left;
    struct treenode *right;
} treenode;

typedef struct tree{
    treenode *root;
    int size;
} tree;

treenode* create_treenode(int value);


// General Functions
int factorial(int n);

#endif // structures_h