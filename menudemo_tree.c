#include <stdio.h>
#include <time.h>
#include "trees.h"

void intro(void);
int get_cmd(void);
void do_cmd(int cmd);


//global var:
tree_node* root;

int main(void){
    root = NULL;

    //generate random tree from root.

    srand( time(NULL) );
    for (int i = 0; i<10; i++){

        int item = rand() % 100;
        insert_node(root, item);
    }


    intro();

    while(1){
        int command = get_cmd();
        do_cmd(command);
        ;
    }
    return 0;
}

void intro(){

    printf("Welcome to the tree demo. \n"
            "-For help, type <h> \n");
}

void help(){
    printf( "Tree Operations: \n"
            "  -insert a node at index (l)" 
            "Tree Traversal: \n" 
            "  -traverse a tree in order, type <o>\n"
            "  -traverse a tree post order, type <l>\n"
            "  -traverse a tree pre order, type <p>\n"
            "To quit, type <q>\n"
            " Press <enter> to continue :)");

    while(getchar() != '\n')
        ;
}

int get_cmd(){

    int cmd;
    while((cmd = getchar()) == '\n');
        ;
    if(cmd == 'h' || cmd == 'i' || cmd == 'o' ||
        cmd == 'l' || cmd == 'p' || cmd == 'q')
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
            break;
        case 'o':
            in_order(root, visit);
            break;
        case 'l':
            post_order(root, visit);
            break;
        case 'p':
            pre_order(root, visit);
            break;
        case 'i':
            printf("Under construction. \n");
            break;        
    }
}
