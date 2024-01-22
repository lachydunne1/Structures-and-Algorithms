#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "trees.h"

void intro(void);
int get_cmd(void);
void do_cmd(int cmd);

/*
  Stuff aint printing yo. 
*/
tree *root;
int main(void){

    //create root.
    root = create_tree();

    //generate random tree from root.
    srand( time(NULL) );
    for (int i = 0; i<10; i++){

        int item = rand() % 100;
        //generate tree, also generates root.
        insert_into_tree(root, item);
    }

    if(root == NULL){
        printf("Root is still NULL \n");
    } else {
        printf("Root is no longer null \n");
    }

    intro();

    while(1){
        
        int cmd = get_cmd();
        do_cmd(cmd);
        
        //handle quit in main
        if(cmd == 'q'){
            break;
        }

    }
    return 1;
}

void intro(){

    printf("Welcome to the tree demo. \n"
            "-For help, type <h> \n");
}

void help(){
    printf( "Tree Operations: \n"
            "  -insert a node at index, type <i>\n" 
            "Tree Traversal: \n" 
            "  -traverse a tree in order, type <o>\n"
            "  -traverse a tree post order, type <l>\n"
            "  -traverse a tree pre order, type <p>\n"
            "To quit, type <q>\n"
            " Press <enter> to continue :) \n");

    while(getchar() != '\n')
        ;
}

int get_cmd(){

    int cmd;
    while((cmd = getchar()) == '\n');
        ;
    if(cmd == 'h' || cmd == 'i' || cmd == 'o' ||
        cmd == 'l' || cmd == 'p' || cmd == 'q')
        
        printf("Executing: %c \n", cmd);
        return cmd;

    printf("Please enter a valid command.\n");
}

void do_cmd(int command){

    switch(command){

        case 'h':
            help();
            break;
        case 'q':
            printf("Bye!\n");
            free_tree(root->root);
            break;
        case 'o':
            //bad naming, access root field in tree
            in_order(root->root, visit);
            break;
        case 'l':
            post_order(root->root, visit);
            break;
        case 'p':
            pre_order(root->root, visit);
            break;
        case 'i':
            int node_value;
            printf("Enter new node value: \n");

            scanf("%i", &node_value);
            insert_into_tree(root, node_value);
            break;        
    }
}
