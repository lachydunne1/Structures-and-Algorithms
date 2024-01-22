#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>


#include "trees.h"
#define MEM_ERROR "Error: You've touched the void."

/*
    Trees:
*/

tree *create_tree(){
    tree *new_tree = (tree *)malloc(sizeof(tree));

    if (new_tree != NULL){
        new_tree->root = NULL;
        new_tree->size = 0;
    } else {
        printf(MEM_ERROR);
    }
    return new_tree;

}

tree_node *create_treenode(int value){

    tree_node* result = (tree_node*)malloc(sizeof(tree_node));

    if (result!= NULL){
        result->left = NULL;
        result->right = NULL;
        result->value = value;
    }
    return result;
}


void insert_node(tree_ptr *tree, int value){

    
    if(*tree == NULL){

        *tree = (tree_ptr)malloc(sizeof(tree_node));
        
        if(*tree!=NULL){
            printf("Found a leaf, inserted: %i \n", value);
            (*tree)-> value = value;
            (*tree)-> left = NULL;
            (*tree)-> right = NULL;

        } else {
            printf(MEM_ERROR);
        }
    }
    //if tree is not empty, recursively search for a leaf.
    else{

        if (value < (*tree)->value){
            //going to have a seg fault... BET
            printf(" -- Searching for a leaf. -- \n");
            insert_node(&((*tree)->left), value);
        } else {
            insert_node(&((*tree)->right), value);
        }
    }

}

void insert_into_tree(tree *t, int value) {
    insert_node(&(t->root), value);
    t->size++;
}


void visit(tree_node *node){
    //for now, visit will print node, which is an integer.
    printf("%i", node->value);
    printf("\n");

}

/*  Traversal:

    In order: travels to the leftmost node leaf node and 
    recursively traverses left->parent->right until rightmost node.

    Post order: visits leftmost node -> right node -> parent node

    Pre order: parent node -> left node -> right node.
*/
void in_order(tree_node *root, void (*visit)(tree_node *tree_entry)){

    if(root!=NULL){
        in_order(root->left, visit);
        visit(root);
        in_order(root->right, visit);
    }
}

void post_order(tree_node *root, void (*visit)(tree_node *tree_entry)){
    
    if(root!=NULL){
        post_order(root->left, visit);
        post_order(root->right, visit);
        visit(root);
    }
}

void pre_order(tree_node *root, void (*visit)(tree_node *tree_entry)){

    if(root!=NULL){
        visit(root);
        pre_order(root->left, visit);
        pre_order(root->right, visit);
    }
}

void free_tree(tree_node *root){

    if(root!=NULL){
        free_tree(root->left);
        free_tree(root->right);
        //free node after children have been freed.
        free(root);
    }
}

/*
    Red-black trees:
*/
