#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "algos.h"
#include "structures.h"

//TODO: Fix sort algos

void intro(void);
void help(void);
int get_cmd(void);
void do_cmd(int cmd);
int sort_csv(int algorithm_select);

#define MAXSIZE 1000
//file name:
char *infile = "rv_data.csv";

//file data size:
double variables[MAXSIZE];

int main(void){

    intro();
    int cmd = get_cmd();
    do_cmd(cmd);

    return 0;
}

void intro(void){

    printf("Welcome to the sort algorithm demo.\n");
    printf("Enter 'h' for help. \n");
}


void help(void){

    printf("Commands: \n"
            "h - help \n"
            "s - sort \n"
            "q - quit \n"
            "Press <enter> to continue");

    while (getchar() != '\n')
        ;
}


int get_cmd(void){

    int cmd;
    printf("Enter a command: ");


    while((cmd = getchar()) == '\n')
        ;

    if(cmd == 'h' || cmd == 'q' || cmd == 's')
        return cmd;

    //if program reaches, print reminder
    printf("Please enter a valid command.\n");
}

//sort csv manages stdin
int sort_csv(int algorithm_select){

    //open file, config to read
    FILE *inptr = fopen(infile, "r+");
    if (inptr == NULL){
        perror("Error opening file");
        return 1;
    }

    // read -> store -> sort -> write
    int iter = 0;
    //could use while(inptr!=EOF), but to catch both max
    //file and eof we use the below:
    while(iter<MAXSIZE && fscanf(inptr, "%lf",&variables[iter]) == 1)
        iter++;

    //return to start of the stream once read
    rewind(inptr);

    switch (algorithm_select){
        
        case 'b':
            bubble_sort_float(variables, MAXSIZE);
            break;
        case 'i':
            insertion_sort_float(variables, MAXSIZE);
            break;

        case 'm':
            printf("Sorry buddy not done yet.");
            break;
    }    

    // Write sorted data back to the file
    for (int i = 0; i < iter; i++) {
        fprintf(inptr, "%lf\n", variables[i]); // Assuming each float is in a new line
    }

    fflush(inptr); // Flush the output buffer
    ftruncate(fileno(inptr), ftell(inptr)); // Truncate the file to the current file position
    fclose(inptr);
    printf("Written sorted array to csv.\n");
    return 0;

}

void do_cmd(int cmd){
    
    switch (cmd){

        case 'h':
            help();
            break;

        case 'q':
            printf("Cya.\n");
            break;
        
        case 's':
            printf("Welcome to sort options."
                    "Please choose from the algorithms below.\n"
                    "b - Bubble sort.\n"
                    "i - Insertion sort.\n"
                    "m - Merge sort. \n" );

            int algorithm_select;
            while ((algorithm_select = getchar()) == '\n')
                ;
            
            if (algorithm_select == 'b' || algorithm_select == 'i' ||
                algorithm_select == 'm'){
                sort_csv(algorithm_select);
            } else {
                printf("Please enter one of the provided options. \n");
            }
    }

}