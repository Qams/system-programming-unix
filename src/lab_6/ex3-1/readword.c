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
	int c = 'A';

	fd = atoi(argv[1]);
	fd2 = atoi(argv[2]);

	while((nread = read(fd, s, sizeof(s))) > 0)
	{
		if(s[0] == '\n')
			count++;
	}
	close(fd);
	write(fd2, &count, sizeof(count));
	close(fd2);
	exit(EXIT_SUCCESS);

	return 0;
}
