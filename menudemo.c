#include <stdio.h>
#include <stdbool.h>

#include "algos.h"
#include "structures.h"

void print(hash_key, hash_value);
void intro(void);
void help(void);
char get_cmd(void);
void do_cmd(char cmd);

int main(void)
{


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

char get_cmd(void)
{
    char cmd;
    printf("Enter a command: \n");
    //wait for command
    while(true){

        while((cmd == getchar()) == '\n');
        
        //check user input for command
        if (cmd == ('h' || 'p' || 'i' || 'd' || 's' || 'q' ))
            while (get_char() != '\n')
                ;
            return cmd;
    }   
    printf("Please enter a valid command or enter <h> for help. \n");
    
}

void do_cmd(char cmd){

    switch (cmd){

        case 'h':
            help();
            break;
        case 'p':
            print_table();
            break;
        case 'i':
            char *word;
            printf("Please enter a word: \n");
            while ((word == get_char()) != '\n');
                ;
            
            if (hash_store_word(word) == true){
                printf("Stored word successfully. \n");
            } else{
                printf("Word wasn't stored successfully \n");
            }
            break;
        case 'd':
            

        case 's':

        case 'q':
    }
}