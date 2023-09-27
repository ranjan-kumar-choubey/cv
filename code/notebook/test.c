/* Q. Write a Program which will take two command line agument
	first argument : line No. of a file
	second argument : File Name
Example : ./test.out <line_number> <input.txt>

*/

#include<stdio.h> 
# include<stdlib.h>
void main(int argc, char **argv)
{
    // printf("argc = %d\n",argc);

	// 	print everything get by command line
    // for(int i=0;i<argc; i++)
    //     printf("argv[%d] = %s\n",i,argv[i]);


	int n = atoi(argv[1]); //string to integer
	if(n<=0)
	{
		printf("Line No must be positive\n");
		exit(1);
	}

	// float f = atof("98981.299999"); //string to float
	// printf("float f = %f\n",f);

	// check you have provided correct no of argument
	if(argc != 3)
        printf("Usage %s <line number> <fileneame> \n",argv[0]);

	// check you are successfully read or not ?
	FILE * fp = fopen(argv[2],"r");
	if (NULL == fp)
		printf("\n could not open the file %s\n",argv[2]);

	//  reading charcter by character & throw 
	int current_line = 1;
	char c;

	while(current_line < n)
	{
		// reading file line by line & dicarding 
		do c = fgetc(fp);  
		while(c != EOF && c != '\n');

		// if less no of lines in file than given value 
		if(c == EOF)
		{
			printf("Not Enough lines \n"); 
			exit(1);
		}
		current_line++;
	}

	// now pointer is pointing to that line , & print that line 
	 while(EOF != (c=fgetc(fp)))
	 {
		putchar(c);
		if(c=='\n')
			break;
	 }

}