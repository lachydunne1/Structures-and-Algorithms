#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>


#include "trees.h"
#define MEM_ERROR "Error: You've touched the void."

/*
    Trees:
*/

tree_node *create_treenode(int value){

    tree_node* result = (tree_node*)malloc(sizeof(tree_node));

    if (result!= NULL){
        result->left = NULL;
        result->right = NULL;
        result->value = value;
    }
    return result;
}

//possibly bad
void insert_node(tree_node *tree_ptr, int value){


    if(tree_ptr == NULL){
        tree_ptr = (tree_node*)malloc(sizeof(tree_node));
        
        if(tree_ptr!=NULL){

            tree_ptr-> value = value;
            tree_ptr-> left = NULL;
            tree_ptr-> right = NULL;

        } else {
            printf(MEM_ERROR);
        }
    }
    //if tree is not empty, recursively call until we find a leaf.
    else{

        if (value < (tree_ptr->value)){
            //going to have a seg fault... BET
            insert_node(tree_ptr->left, value);
        }
    }

}

void visit(tree_node *node){
    //for now, visit will print node, which is an integer.

    putchar(node->value);
    putchar('\n');

}

/*TODO: Implement in_order, post_order and pre_order traversal.

    In order: travels to the leftmost node leaf node and 
    recursively traverses left->parent->right until rightmost node.

    Post order: visits leftmost node -> right node -> parent node

    Pre order: parent node -> left node -> right node.
*/
void in_order(tree_node *root, void (*visit)(tree_node *tree_entry)){
    
    if(root!=NULL){
        in_order(root->left, visit);
        visit(root->value);
        in_order(root->right, visit);
    }


}

void post_order(tree_node *root, void (*visit)(tree_node *tree_entry)){

    if(root!=NULL){
        post_order(root->left, visit);
        post_order(root->right, visit);
        visit(root->value);
    }
}

void pre_order(tree_node *root, void (*visit)(tree_node *tree_entry)){

    if(root!=NULL){
        visit(root->value);
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

