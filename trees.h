#ifndef trees_h
#define trees_h

#include <stdint.h>
#include <stdbool.h>
#include <stdint.h>

// Trees

typedef struct tree_node{
    int value;
    struct tree_node *left;
    struct tree_node *right;
} tree_node;

typedef struct tree{
    tree_node *root;
    int size;
} tree;

tree_node* create_treenode(int value);
void insert_node(tree_node *tree_ptr, int value);
void visit(tree_node *node);
void in_order(tree_node *root, void(*visit)(tree_node *tree_entry));
void post_order(tree_node *root, void(*visit)(tree_node *tree_entry));
void pre_order(tree_node *root, void(*visit)(tree_node *tree_entry));

void free_tree(tree_node *root);
#endif // trees_h