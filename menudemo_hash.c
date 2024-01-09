#include <stdio.h>
#include <stdbool.h>

#include "algos.h"
#include "structures.h"

void intro(void);
void help(void);
int get_cmd(void);
void do_cmd(int cmd);

/*
    TODO: Fix core dump in hash function (I think)
*/

int main(void)
{
    //initialize hash function with null pointers
    hash_init();
    intro();

    while(1)
        do_cmd(get_cmd());
    return 1;
}


void intro(void)
{
    printf("Welcome to the hash table demo.\n");
    printf("Enter 'h' for help.\n");
}

void help(void)
{
    printf("Commands:\n"
            "h - help\n"
            "p - print hash index\n"
            "i - insert a word\n"
            "d - delete a word\n"
            "s - search for a word\n"
            "q - quit\n"
            "Press <Enter> to continue\n");
            
    while (getchar() != '\n')
        ;
}

int get_cmd(void)
{
    int cmd;
    printf("Enter a command: ");
    //wait for command
    
    while((cmd = getchar()) == '\n')
        ;
    //check user input for command
    if (cmd == 'h' || cmd == 'p' || cmd == 'i' ||
        cmd == 'd' || cmd == 's' || cmd ==  'q' )
        return cmd;
 
    printf("Please enter a valid command or enter <h> for help. \n");
    
}

void do_cmd(int cmd)
{    
    //used with scanf to store a word. This function should only
    //be executed once on command, word is updated. This may be a 
    //source of error.
    char word[HASH_LENGTH];

    switch (cmd){

        case 'h':
            help();
            break;

        case 'p':
            print_table();
            break;

        case 'i':

            printf("Please enter a word: ");
            //specify size of word to avoid overflow
            scanf("%45s", word);
            

            if (hash_store_word(word) == true){
                printf("Stored word successfully. \n");
            } else{
                printf("Word wasn't stored successfully \n");
            }
            break;

        case 'd':

            printf("Enter the word you would like to delete: ");
            scanf("%45s", word);

            if (hash_delete_word(word) == true){
                printf("Word was deleted successfully. \n");
            } else{
                printf("The word couldn't be found. \n");
            }
            break;

        case 's':
            printf("What word would you like to checK? ");
            scanf("%45s", word);

            if (check_word(word) == true){
                printf("Word was found at hash index: %i.", hash(word));
                printf("\n");
            }else{
                printf("Word wasn't stored at index location. \n");
            }
            break;

        case 'q':
            printf("Bye for now! \n");
            break;
    }
}