#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
     
int main(int argc, char *argv[]){

	int tab[10];
	int i;
	
	int fdOut2 = atoi(argv[1]);	

	for(i=0;i<10;i++)
	{
		tab[i] = i+1;
		write(fdOut2, &tab[i], sizeof(int));
	}

	
	return 0;
}
