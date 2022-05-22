#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

/* @requires nothing
   @assings nothing
   @ensures returns an empty stack */
Stack empty_stack() {
    return NULL;
}

/* @requires s is a valid stack
   @assings nothing
   @ensures returns 1 if the stack is empty and 0 otherwise */
int is_empty_stack(Stack s) {
    return (s == NULL);
}

/* @requires s is a valid pointer to a stack
   @assings add x at the top of the stack
   @ensures nothing */
void push_stack(Stack *s, int x) {
    // allocate the memory for a res stack :
    Stack res = malloc(sizeof(Stack));
    // check if the memory was correctly allocated :
    if (res == NULL) {
        printf("Memory allocation error.\n");
        exit(1);
    }
    // add x at the top of res :
    res->top = x;
    // add s at the end of res :
    res->next = *s;
    // change s into res :
    *s = res;
}

/* @requires s is a valid pointer to a stack
   @assings removes the value at the top of the stack
   @ensures returns the top of the stack */
int pop_stack(Stack *s) {
    // check if the stack is empty :
    if (*s == NULL) {
        printf("The stack is empty.\n");
        exit(1);
    }
    // put the value at the top of the stack in a top variable :
    int top = (*s)->top;
    // delete the value at the top of the stack :
    (*s) = (*s)->next;
    // return the value of top :
    return top;
}

/*  @requires s is a valid stack
    @assigns nothing
    @ensures prints the stack s */
void print_stack(Stack s) {
    // check if the stack is empty :
    if (is_empty_stack(s)) {
        printf("The stack is empty.\n");
    }
    else {
    // the last bucket of a stack is always equal to NULL, at each iteration we are moving to the next bucket :
    while (!is_empty_stack(s)) {
        // print each value of the stack :
        printf("-> [ %i ] ", s->top);
        // moving to the next value :
        s = s->next;
    }
    printf("\n");
    }
}
