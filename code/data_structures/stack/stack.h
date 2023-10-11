#ifndef STACK_H  //conditional compilation pre-preocssing directives, this is for, not going into INF loop of adding Header files
#define STACK_H 


#include<stdlib.h>
#include<stdio.h>

typedef int DATA; // We can also try typedef char * DATA;
typedef struct 
{
    int capacity;
    int top;
    DATA *elements;

} STACK;

// function Declaration only, Not Defintion (extern means it can be used by other files)
extern STACK create_stack(unsigned int capacity);
extern int push(STACK *s, DATA *d);
extern int pop(STACK *s);
extern void stack_print(STACK *s);


 #endif
