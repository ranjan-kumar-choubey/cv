#ifndef QUEUE_H  //conditional compilation pre-preocssing directives, this is for, not going into INF loop of adding Header files
#define QUEUE_H 


#include<stdlib.h>
#include<stdio.h>

typedef int DATA; // We can also try typedef char * DATA;
typedef struct 
{
    int capacity;
    int num_elements;
    int front;
    int rear;
    DATA *elements;

} QUEUE;

// function Declaration only, Not Defintion (extern means it can be used by other files)
extern QUEUE create_queue(unsigned int capacity);
extern int enqueue(QUEUE *s, DATA *d);
extern int dequeue(QUEUE *s);
extern void QUEUE_print(QUEUE *s);


 #endif