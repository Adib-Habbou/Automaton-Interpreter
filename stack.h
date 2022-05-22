#ifndef STACK_H
#define STACK_H

/*  implementation of stack with linked list where the value of the first bucket represents the top of the stack*/
struct base_stack {
   int top;
   struct base_stack *next;
};
typedef struct base_stack *Stack;

/* @requires nothing
   @assings nothing
   @ensures returns an empty stack */
Stack empty_stack();

/* @requires s is a valid stack
   @assings nothing
   @ensures returns 1 if the stack is empty and 0 otherwise */
int is_empty_stack(Stack s);

/* @requires s is a valid pointer to a stack
   @assings adds x at the top of the stack
   @ensures nothing */
void push_stack(Stack* s, int x);

/* @requires s is a valid pointer to a stack
   @assings removes the value at the top of the stack
   @ensures returns the top of the stack */
int pop_stack(Stack* s);

/*  @requires s is a valid stack
    @assigns nothing
    @ensures prints the stack s */
void print_stack(Stack s);

#endif
