/*
compile this file using below command
>> gcc -g -Wall stack.h stack-testing.c

After testing is complete , compile stack.c sepeartely
>> gcc -g -Wall -c stack.c   // it will create stack.o , an object file, bcause of no main


Extra Note : gcc -E file.c // it will only pre-precessing, it will add signatur eof function only,
linker will add all compiled function defintion during linking time
linker
*/

#include <stdio.h>
#include "stack.h"

int main()
{
    printf("Testing Stack Operation ...\n");


    STACK S = create_stack(10);
    // int x;
    // STACK S;
    // // Menu
    // printf("\nEnter\n C : create stack\n I : push \n D : pop \n P : Print\n q : Quit...\n");
    // while (1)
    // {
    //     char input;
    //     scanf("%c", &input);
    //     printf("\nWhat do you want Now ? Enter : ");
        

    //     switch (input)
    //     {

    //     case 'C': // Create New Stack
    //         printf("\nEnter Size of Satck : ");
    //         int n;
    //         scanf("%d", &n);

    //         S = create_stack(n);
    //         break;

    //     case 'P': // printing stack
    //         stack_print(&S);
    //         break;

    //     case 'I': // Push Operation
    //         printf("\nEnter Number to Insert : ");

    //         scanf("%d", &x);

    //         if (0 == push(&S, &x))
    //             printf("Stack Overflow! Can't push %d", x);
    //         else
    //             printf("\n%d is Pushed\n", x);
    //         break;

    //     case 'D': // Pop Operation
    //         x = pop(&S);
    //         if (0 == x)
    //             printf("\nStack UnderFlow! Can't pop");
    //         else
    //             printf("\n%d is popped", x);

    //         break;

    //     case 'q':
    //         printf("\nThik Hai..");
    //         exit(1);
    //     }
// }

        for(int i =1 ;i<100;i++)
            if(0==push(&S,&i)){
                printf("Stack Overflow! Can't push %d\n",i);
                return 0;
            }
            else
                printf("\n%d is Pushed",i);

        for(int i =1 ;i<11;i++)
            printf("\t%d",pop(&S));
    
}
