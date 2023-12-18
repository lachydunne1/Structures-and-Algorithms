#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "structures.h"

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

/* Hash Function:
    Takes a pointer to a char (an array of string literals), 
    returns a hash index for each string literal, resulting 'unique'
    hash index, ignoring collsions
*/

// strange scope here - declared in h file too.
// declared on top of source due to the need for the hash table in functions
#define HASH_LENGTH 100
#define buckets 10000
hash_node* hash_table[buckets];

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

void hash_init(){
    for (int i = 0; i < buckets; i++) {
        hash_table[i] = NULL;
    }
}
void print_table(){
    //print empty and stored names in hash table. \t placeholder is tab.
    for (int i = 0; i < HASH_LENGTH; i++){
        if (hash_table[i] == NULL){
            printf("\t%i\t---\n",i);
        } else{
            printf("\t%i\t%s\n",i, hash_table[i]->word);
        }
    }

}

bool hash_store_word(const char *word)
{
    hash_node *new_node = malloc(sizeof(hash_node));
    if (new_node == NULL)
    {
        printf("Failed to allocate space for new node. \n");
        return false;
    }

    
    int32_t hashed = hash(word);
    //copy word into node
    strcpy(new_node->word, word);
    printf("Hash key: %i\n", hashed);
    
    if (hash_table[hashed] == NULL){
        //store word in new node
        hash_table[hashed] = new_node;
        new_node->next = NULL;
    }
    else{
        //if word exists in hash table, we can
        //use the same index to extend it.
        new_node->next = hash_table[hashed];
        hash_table[hashed] = new_node;
    }
    return true;
}

bool hash_delete_word(const char *word)
{
    int hashed = hash(word);
    hash_node *current = hash_table[hashed];
    hash_node *previous = NULL;

    while (current != NULL) {
        if (strcmp(current->word, word) == 0){
            //word was found
            if(previous == NULL){
                //word is at head of the list
                hash_table[hashed] = current->next;
            } else {
                //word is in the middle or end of the list
                previous->next = current->next;
            }
            //works as when word is stored in hash, we use malloc.
            free(current);
            return true;
        }
    }
    //word wasn't found.
    return false;
}

//hashes a file in pathway and stores in table. Dictionary size should be
//0 initially.
bool hash_file(const char *dictionary, uint16_t dictionary_size)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL){
        fclose(file);
        printf("Couldn't open %s.\n", dictionary);
        return false;
    }

    char word[HASH_LENGTH + 1];
    
    while (fscanf(file, "%s", word) != EOF)
    {   
        //allocate memory for a new node
        hash_node *new_node = malloc(sizeof(hash_node));
        if (new_node == NULL){
            fclose(file);
            printf("Couldn't allocate memory for new node. \n");
            return false;
        }

        //copy word into node
        strcpy(new_node->word, word);

        //hash word to index for table
        int hashed = hash(word);

        //if word is new, allocate new memory, otherwise use 
        //existing structure
        if (hash_table[hashed] == NULL)
        {
            hash_table[hashed]= new_node;
            new_node ->next = NULL;
        }
        else 
        {
            new_node->next =hash_table[hashed];
            hash_table[hashed] = new_node;
        }

        dictionary_size++;
    }
    fclose(file);
    return true;
}

bool check_word(const char* word)
{
    //get index for word
    int index = hash(word);
    
    for (hash_node *temp = hash_table[index]; temp != NULL; temp = temp->next)
    {
        if (strcmp(temp->word, word) == 0){
            printf("Word is in hash table. \n");
            return true;
        }
    }
    printf("Word isn't in hash table. \n");
    return false;

}


/* Singly Linked List:
    Below are some setup functions/structs for singly linked lists.
*/

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
int push(stack* stck, int value) {
    stacknode* new_node = (stacknode*) malloc(sizeof(stacknode));
    if (new_node == NULL){
        return -1; //handle malloc failure
    }
    new_node->value = value; // arrange new node value
    new_node->next = stck->top; // set the next pointer of the new node to the current top
    stck->top = new_node; //  make new node as top of stack
    stck->size++; // increase stack size
    return 0;
}

/* Pop:
    Removes top value from the stack and returns it.
*/
int pop(stack* stck){
    if(stck->size == 0){
        return -1; // stack is empty
    }
    stacknode *temp = stck->top; //use temp pointer to point to top
    int popped = temp->value; //assign value of top of stack to popped
    free(temp); // free temp to avoid memory leaks
    stck->size--; //decrement stack size
    return popped;
}

/* Peek:
    Returns the top value from the stack without removing it.
*/
int peek(stack* stck){
    if(stck->size == 0){
        return -1; //empty stack
    }
    return stck->top->value; // dereference and point to top value in stack
}
/* stack_is_empty:
    checks if stack is empty
*/
bool stack_is_empty(stack* stck){
    return ((stck->size)==0);
}

/* stack_size:
    returns stack size
*/
int stack_size(stack* stck){
    return stck-> size;
}

/* free_stack:
    frees the memory allocated for the stack and its nodes
*/

void free_stack(stack* stck){
    while(stck->size != 0){ // loop until stack is empty
        pop(stck); //free top node
    }
    free(stck); //once reached, free bottom node
}


/*
    Trees:
*/
treenode *create_treenode(int value){

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

