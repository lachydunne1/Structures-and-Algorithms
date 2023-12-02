#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define HASH_LENGTH 45 // length of word in node (for hash tables)
/*
    This ad-hoc library contains sort algos and shitty data structures
    so that I can attempt to keep track of them. They will be poorly defined
    and documentated. You have been warned.
*/

/*
    Data Structures:
    Hash table: The hash table is defined by two functions, the node and
    the hash function.

    Singly-linked list: Singly linked list, defined with sllnode struct.
    in order to use this, you will need to dynamically allocate memory for
    an sllnode, check if null (No space), initialize the nodes value field and
    next field, then return a pointer to the newly created sllnode. Note that
    the current value for the sllnode is int, but is interchangeable.

*/

unsigned int size(void);

int32_t hash(const char *word);



typedef struct hash_node
{
    char word[HASH_LENGTH + 1];
    struct hash_node *next;
}hash_node;

/* Hash Function:
    Takes a pointer to a char (an array of string literals), 
    returns a hash index for each string literal, resulting 'unique'
    hash index, ignoring collsions
*/
int32_t hash(const char *word)
{
    int32_t prime = 982451653;
    int i, hashIndex = 0;
    for(i=0; i<strlen(word); i++)
    {
        hashIndex+=word[i];
    }
   return hashIndex % prime;
}

/* Singly Linked List:
    Below are some setup functions/structs for singly linked lists.
*/
typedef struct sllnode
{
    int val; // can be an aribtrary datatype
    struct sllnode* next;
}sllnode;

typedef struct sllist
{
    int count;
    sllnode *head;
}sllist;

int get_sll_length(sllnode* head)
{
    int length = 0;
    sllnode* current = head;

    while (current!=NULL){
        length++;
        current = current->next;
    }
    return length;
}

void clear_sll(sllist* seq)
{
    //get head
    sllnode* current = seq->head;
    //scan through sllist
    while (current != NULL){
        //while list dinnae equal null,
        //assign temps to be cleared iteratively while
        //saving position in current.
        sllnode* temp = current;
        current = current->next;
        free(temp);
    }

}
/* Stack:
    Below are defintions of stack structs and some peripheral functions
*/

/* Stack Node and Stack:
    Stack node contains an integer value and a pointer to the next node in the stack.
    Stack contains a pointer to the top node and int to keep track of size.
*/
typedef struct stacknode {
    int value;
    struct stacknode* next;
} stacknode;

typedef struct {
    stacknode* top;
    int size;
} stack;

/* Create Stack:
    Intializes and empty stack and returns its pointer.
*/
stack* create_stack() {
    stack* new_stack = (stack*) malloc(sizeof(stack));
    if (new_stack == NULL){
        //handles malloc failure
        return NULL;
    }
    new_stack->top = NULL;
    new_stack->size = 0;
    return new_stack;
}

/* Push:
    Adds a new value to the top of the stack
*/
int push(stack* stack, int value) {
    stacknode* new_node = (stacknode*) malloc(sizeof(stacknode));
    if (new_node == NULL){
        return -1; //handle malloc failure
    }
    new_node->value = value; // arrange new node value
    new_node->next = stack->top; // set the next pointer of the new node to the current top
    stack->top = new_node; //  make new node as top of stack
    stack->size++; // increase stack size
    return 0;
}

/* Pop:
    Removes top value from the stack and returns it.
*/
int pop(stack* stack){
    if(stack->size == 0){
        return -1; // stack is empty
    }
    stacknode *temp = stack->top; //use temp pointer to point to top
    int popped = temp->value; //assign value of top of stack to popped
    free(temp); // free temp to avoid memory leaks
    stack->size--; //decrement stack size
    return popped;
}

/* Peek:
    Returns the top value from the stack without removing it.
*/
int peek(stack* stack){
    if(stack->size == 0){
        return -1; //empty stack
    }
    return stack->top->value; // dereference and point to top value in stack
}
/* stack_is_empty:
    shecks if stack is empty
*/
void stack_is_empty(stack* stack){
    return (stack->size==0);
}

/* stack_size:
    returns stack size
*/
int stack_size(stack* stack){
    return stack-> size;
}

/* free_stack:
    frees the memory allocated for the stack and its nodes
*/

void free_stack(stack* stack){
    while(stack->size != 0){ // loop until stack is empty
        pop(stack); //free top node
    }
    free(stack); //once reached, free bottom node
}
typedef struct treenode{
    int value;
    struct treenode *left;
    struct treenode *right;
} treenode;

typedef struct tree{
    treenode *root;
    int size;
} tree;

treenode *create_treeenode(int value){

    treenode* result = (treenode*) malloc(sizeof(treenode));
    if (result!= NULL){
        result->left = NULL;
        result->right = NULL;
        result->value = value;
    }
    return result;
}
/*
    General Functions:
    factorial: As is, computes the factorial.
*/

int factorial(int n)
{
	if (n==0)
		return 1;
	else
	 	return n* factorial(n - 1);
}

