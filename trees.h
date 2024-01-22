#ifndef trees_h
#define trees_h

#include <stdint.h>
#include <stdbool.h>
#include <stdint.h>

/*Basic Tree*/

typedef struct tree_node{
    int value;
    struct tree_node *left;
    struct tree_node *right;
} tree_node;

typedef struct tree{
    tree_node *root;
    int size;
} tree;

typedef tree_node* tree_ptr;

tree* create_tree(void);
tree_node* create_treenode(int value);

void insert_node(tree_ptr *root, int value);
void insert_into_tree(tree *t, int value);
void visit(tree_node *node);
void in_order(tree_node *root, void(*visit)(tree_node *tree_entry));
void post_order(tree_node *root, void(*visit)(tree_node *tree_entry));
void pre_order(tree_node *root, void(*visit)(tree_node *tree_entry));

void free_tree(tree_node *root);


/*
    Self Balancing Trees

*/

/* Red-Black tree */

typedef struct rb_treenode{
    int value;
    bool red;
    struct rb_treenode *left;
    struct rb_treenode *right;
}rb_treenode;
/* RB-Tree outcomes:

    OK: Colour of the current root has not changed; the tree now
    satisfies the conditions for a red-black tree.

    REDNODE: The current root has changed from black to red; modification
    may or may not be needed to restore rb-tree properties.

    RIGHTRED: The current root and its right child are now both red;
    a colour flip or rotation is needed.

    LEFTRED: The current root and its left child are now both red;
    a colour flip or rotation is needed.

*/
typedef enum rb_oc {OK, REDNODE, RIGHTRED, LEFTRED } rb_outcome;

#endif // trees_h