#ifndef structures_h
#define structures_h

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define HASH_LENGTH 45 // length of word in node (for hash tables)
#define buckets 10000
// Hash Table

typedef struct hash_node {
    const char word[HASH_LENGTH + 1];
    struct hash_node *next;
} hash_node;


extern hash_node* hash_table[];

unsigned int size(void);
int32_t hash(const char *word);

void hash_init(void);
void print_table(void);
bool hash_store_word(const char *word);
bool hash_delete_word(const char *word);
bool hash_file(const char *dictionary, uint16_t dictionary_size);
bool check_word(const char *word);

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

stack* create_stack(void);
int push(stack* stck, int value);
int pop(stack* stck);
int peek(stack* stck);
bool stack_is_empty(stack* stck);
int stack_size(stack* stck);
void free_stack(stack* stck);

// Sorting Algorithms
void bubble_sort(int* arr, int numsSize);
void ms_divide(sllist *list, sllist *secondhalf);
void merge(sllist *first, sllist *second, sllist *out);
void merge_sort(sllist *list);




// General Functions
int factorial(int n);

#endif // structures_h