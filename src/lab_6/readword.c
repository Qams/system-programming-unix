#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
     
int main(int argc, char *argv[]){
	
	int fd, fd2, len;
	int count = 0;
	int fileLength = 1;
	ssize_t nread;
	char s[1];
	int c;

	fd = atoi(argv[1]);
	fd2 = open(argv[2], O_RDONLY);

	while((nread = read(fd2, s, sizeof(s))) > 0)
	{
		if(s[0] == '\n')
			count++;
	}

	//printf("Liczba linii: %d\n", count);
	write(fd, &count, sizeof(count));
	exit(EXIT_SUCCESS);

	return 0;
}
