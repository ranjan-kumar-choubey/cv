#include<stdio.h>
#include<stdlib.h>

typedef struct{
	int size;
	char **array;
}LIST;

LIST create_list(void){
	LIST l;
	l.size=0;
	l.array=NULL;
	return l;
}

void print_list(LIST L){
	int i;
	if(L.size==0)
		printf("List is empty.");
	else{
	//printf("The list is: ");
	printf("(%s",L.array[0]);
	for(i=1;i<L.size;i++)
		printf(", %s ",L.array[i]);
	printf(")\n");
	}
}

LIST append(LIST L,char *a){
	L.size++;
	if(NULL==(L.array=(char**)realloc(L.array,L.size*sizeof(char*))))
		{ printf("OVERFLOW..."); exit(1); }
	L.array[L.size-1]=(char*)realloc(L.array[L.size-1],9*sizeof(char));
	L.array[L.size-1]=a;
	return L;
}

/*LIST prepend(LIST L,char *a){
	int i;
	L.size++;
	if(NULL==(L.array=(char**)realloc(L.array,L.size*sizeof(char*))))
		{ printf("OVERFLOW..."); exit(1); }
	L.array[L.size-1]=(char*)realloc(L.array[L.size-1],9*sizeof(char));
	for(i=L.size-1;i>0;i--)
		L.array[i]=L.array[i-1];
	L.array[0]=a;
	return L;
}

LIST deletelast(LIST L){
	if(NULL==(L.array=(char**)realloc(L.array,L.size*sizeof(char*))))
		{ printf("UNDERFLOW...."); exit(1);}
	L.size--;
	L.array=(char**)realloc(L.array,L.size*sizeof(char*));
	return L;
}

LIST deletefirst(LIST L){
	int i;
	for(i=0;i<L.size-1;i++)
	{
		L.array[i]=L.array[i+1];
	}
	if(NULL==(L.array=(char**)realloc(L.array,L.size*sizeof(char*))))
		{ printf("UNDERFLOW...."); exit(1);}
	L.size --;	
	L.array=(int*)realloc(L.array,L.size*sizeof(int));
	return L;	
}

LIST deleteall(LIST L,int a){
	int i,j;
	for(i=L.size-1;i>=0;i--)
	{
		if(L.array[i]==a)
		{
			for(j=i;j<L.size-1;j++)
				L.array[j]=L.array[j+1];
			L.size--;
			if(NULL==(L.array=(char**)realloc(L.array,L.size*sizeof(char*))))
				exit(1);
		}
	}
	return L;
}*/


int main()
{
	LIST p;
	p=create_list();
	p=append(p,"apple");
	//p=prepend(p,"lemon");
	//p=deletelast(p);
	/*p=append(p,2);
	p=append(p,3);
	p=append(p,6);
	p=append(p,7);
	p=append(p,8);
	p=append(p,4);
	p=append(p,2);
	p=append(p,3);
	p=prepend(p,9);
	p=prepend(p,2);
	p=prepend(p,4);
	p=prepend(p,8);
	p=prepend(p,2);
	p=prepend(p,5);
	p=prepend(p,9);
	p=prepend(p,8);
	p=prepend(p,9);
	p=prepend(p,1);
	p=deletelast(p);
	p=deletelast(p);
	p=deletelast(p);
	p=deletelast(p);
	p=deletelast(p);
	p=deletefirst(p);
	p=deletefirst(p);
	p=deletefirst(p);
	p=deletefirst(p);
	p=deletefirst(p);
	p=deleteall(p,7);
	p=deleteall(p,2);
	p=deleteall(p,9);
	p=deleteall(p,4);
	p=deleteall(p,7);
	printf("\n");*/
	print_list(p);
}


