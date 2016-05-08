#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
     
int main(int argc, char *argv[]){

	int fd;
	ssize_t nread;
	char s[100];

	fd = atoi(argv[1]);
	printf("Reading file descriptor %d\n", fd);
	nread = read(fd, s, sizeof(s));
	if(nread != -1)
	{
		if(nread == 0)
			printf("EOF\n");
		else
		{
			printf("Read %ld bytes: %s\n", (long)nread,s);
			exit(EXIT_SUCCESS);
		}
	}
	else
	{
		exit(EXIT_FAILURE);
	}

	
	return 0;
}

