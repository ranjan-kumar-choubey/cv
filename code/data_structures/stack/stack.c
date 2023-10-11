//  this file will not have main() function, it only have function defintion of stach.h files content
#include "stack.h"

extern STACK create_stack(unsigned int capacity)
{
    STACK S;
    S.capacity = capacity;
    S.top = -1;
    S.elements = (int *)malloc(sizeof(S.capacity));

    return S;
}
extern int push(STACK *s, DATA *d)
{
    if (s->top == s->capacity - 1)
        return 0; // stack overflow

    s->top += 1;
    s->elements[s->top] = *d;
    return 1;
}

extern int pop(STACK *s)
{
    if (s->top == -1)
        return 0;

    int temp = s->elements[s->top];
    s->top -= 1;
    return temp;
}

extern void stack_print(STACK *s)
{
    
    int temp = s->top;

    if (temp == -1 || s==NULL)
    {
        printf("\nThere is No Stack! ");
        return;
    }

    printf("\nStack Items : ");
    while (temp >= 0)
    {
        printf("\t %d", s->elements[temp]);
        temp -= 1;
    }
}