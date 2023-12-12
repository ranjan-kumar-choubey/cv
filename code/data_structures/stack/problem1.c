#include<stdio.h>
#include<stdlib.h>

int main(int argc, char** argv)
{   
    // if file doesn't exit then It will return NULL Pointer
    FILE* fp = fopen(argv[1],"r");
    // so we need to handle this case
    if(fp==NULL) 
    {
        printf("files Doesn' exit\n"); //this will write output into output.txt
        // fprintf(stderr,"files Doesn' exit\n"); // try to compile like problem.out input.txt 
    }
    int c ;
    while (EOF!=(c=fgetc(fp)))
    {
        printf("%c\t",c);
    }
    

}