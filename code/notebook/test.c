#include<stdio.h>

#define NUM_BINS 10

int hist[NUM_BINS];

int main(int ac, char *av[])
{
   int x;
	// intialize array with zero
	for (int i = 0 ;i<NUM_BINS;i++)
		hist[i] = 0;
	
	// Take input one by one and count 
    while (1 == scanf("%d", &x)) {
		int index = x/100;
		if (index>=0 && index < NUM_BINS)
			hist[index] ++;
       
    }

	// print Histogram
	for(int i = 0;i <NUM_BINS; i++)
		printf(" %d",hist[i]);

    return 0;
}
