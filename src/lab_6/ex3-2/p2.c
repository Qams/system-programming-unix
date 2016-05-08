#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
     
int main(int argc, char *argv[]){
	
	int value, i, toSend;
	int fdIn2 = atoi(argv[1]);
	int fdOut = atoi(argv[2]);	

	for(i=0;i<10;i++)
	{
		read(fdIn2, &value, sizeof(int));
		toSend = value*5;
		write(fdOut, &toSend, sizeof(int));
	}

	
	return 0;
}
