#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "matrix.h"

int main(int argc, char** argv) {

    // check that the number of arguments is the right one, otherwise report the error :
    if (argc != 2) {
        printf("%i is not the number of arguments expected.\n", argc);
        exit(1);
    }

    // collect the name of the file entered by the user :
    char* file_name = argv[1];

    // open the file in binary read-only mode :
    FILE* file = fopen(file_name, "rb");

    // check that the file was correctly opened, otherwise report the error :
    if (file == NULL) {
        printf("Error occured while opening the file.\n");
        exit(2);
    }

    // collect the number of states of the automaton :
    char first_line[256]; // first line value
    if (fgets(first_line, 256, file) == NULL) {
        printf("Error occured while reading the first line of the file.\n");
        exit(4);
    }
    int nb_state = atoi(&first_line[2]);

    // print the number of state :
    // printf("%i\n", nb_state);

    // collect all the values of action(s, c) :
    Matrix action = create_matrix(nb_state, 128);
    char buf_action; // action value
    int i, j; // for loop variables
    for (i = 0; i < action.row; i += 1) {
        for (j = 0; j < action.column; j += 1) {
            if (fread(&buf_action, 1, 1, file) != 1) {
                printf("Error occured while reading the file.\n");
                exit(5);
            }
            action.tab[i][j] = (int) buf_action;
        }
    }
    // skip the line break :
    if (fread(&buf_action, 1, 1, file) != 1) {
        printf("Error occured while reading the file.\n");
        exit(5);
    }

    // print the matrix of action :
    // print_matrix(action);
    // printf("\n");

    // collect all the values of reduce(s) :
    Matrix reduce = create_matrix(2, nb_state);
    unsigned char buf_reduce; // reduce value
    int k; // for loop variable

    // collect all the values of the first component of reduce(s) :
    for (k = 0; k < nb_state; k += 1) {
        if (fread(&buf_reduce, 1, 1, file) != 1) {
            printf("Error occured while reading the file.\n");
            exit(5);
        }
        reduce.tab[0][k] = (int) buf_reduce;
    }
    // skip the line break :
    if (fread(&buf_reduce, 1, 1, file) != 1) {
        printf("Error occured while reading the file.\n");
        exit(5);
    }
    
    // collect all the values of the second component of reduce(s) :
    for (k = 0; k < nb_state; k += 1) {
        if (fread(&buf_reduce, 1, 1, file) != 1) {
            printf("Error occured while reading the file.\n");
            exit(5);
        }
        reduce.tab[1][k] = (int) buf_reduce;
    }
    // skip the line break :
    if (fread(&buf_reduce, 1, 1, file) != 1) {
        printf("Error occured while reading the file.\n");
        exit(5);
    }

    // print the matrix of reduce :
    // print_matrix(reduce);
    // printf("\n");

    // collect all the values of shift(s, c) :
    Matrix shift = create_matrix(nb_state, 128);
    char buf_shift[3]; // shift values
    if (fread(&buf_shift, 1, 3, file) != 3) {
        printf("Error occured while reading the file.\n");
        exit(5);
    }
    // the sequence ends with a group of 3 bytes '\255' '\255' '\255'
    while(buf_shift[0] != '\255' && buf_shift[1] != '\255' && buf_shift[2] != '\255') {
        shift.tab[(int) buf_shift[0]][(int) buf_shift[1]] = (int) buf_shift[2];
        if (fread(&buf_shift, 1, 3, file) != 3) {
            printf("Error occured while reading the file.\n");
            exit(5);
        }
    }

    // print the matrix of shift :
    // print_matrix(shift);
    // printf("\n");

    // collect all the values of link(s, A) :
    Matrix link = create_matrix(nb_state, 128);
    char buf_link[3]; // link values
    if (fread(&buf_link, 1, 3, file) != 3) {
        printf("Error occured while reading the file.\n");
        exit(5);
    }
    // the sequence ends with a group of 3 bytes '\255' '\255' '\255'
    while(buf_link[0] != '\255' && buf_link[1] != '\255' && buf_link[2] != '\255') {
        link.tab[(int) buf_link[0]][(int) buf_link[1]] = (int) buf_link[2];
        if (fread(&buf_link, 1, 3, file) != 3) {
            printf("Error occured while reading the file.\n");
            exit(5);
        }
    }

    // print the matrix of link :
    // print_matrix(link);
    // printf("\n");

    // close the file once we have finished collecting all the data needed and verify if its correctly closed :
    if (fclose(file) == 0) {
        printf("File '%s' correctly read. Please enter your inputs.\n", file_name);
    }
    else {
        printf("Error occured while closing the file.\n");
        exit(3);
    }

    // collect the string entered by the user :
    char buf[256]; // user input
    if (fgets(buf, 256, stdin) == NULL) {
        printf("Error occured while reading the input.\n");
        exit(6);
    }

    // initialize the state stack with 0 as initial state :
    Stack state = empty_stack();
    push_stack(&state, 0);

    // browse the string entered by the user :
    int l = 0; // for loop variable
    int len = strlen(buf); // collect the length of the string entered by the user
    // the while loop will end because of break if the input is accepted or rejected, or because the value of l will become greater than len + 1
    while (l < len + 1) {
        // for each character we apply action :
        int result = action.tab[state->top][(int) buf[l]];
        // if the result is 0 we reject :
        if (result == 0) {
            printf("Rejected\n");
            // when a word is not recognized it indicates where in the entry the error occurred :
            if ((int) buf[l] == 10) {
                printf("Character %i not recognized is a line break.\n", l+1);
            }
            else if ((int) buf[l] == 32) {
                printf("Character %i not recognized is a space.\n", l+1);
            }
            else {
                printf("Character %i not recognized : %c\n", l+1, buf[l]);
            }
            break;
        }
        // if the result is 1 we accept :
        if (result == 1) {
            printf("Accepted\n");
            break;
        }
        // if the result is 2 we shift :
        if (result == 2) {
            // push shift(s, c) :
            push_stack(&state, shift.tab[state->top][(int) buf[l]]);
            // go to the next character :
            l += 1;
        }
        // if the result is 3 we reduce :
        if (result == 3) {
            // reduce(s, c) is (n, A) :
            int n = reduce.tab[0][state->top];
            char A = reduce.tab[1][state->top];
            // pop n times, the current state becomes s' :
            int t; // for loop variable
            for (t = 0; t < n; t += 1) {
                pop_stack(&state);
            }
            // push link(s', A) and don't go to the next character :
            push_stack(&state, link.tab[state->top][(int) A]);
        }
        // print the stack for each iteration :
        // print_stack(state);
    }
    
    // empty the memory allocated during the creation of the matrices :
    free_matrix(action);
    free_matrix(reduce);
    free_matrix(shift);
    free_matrix(link);

    return 0;

}
