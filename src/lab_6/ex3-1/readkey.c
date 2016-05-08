#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
     
int main(int argc, char *argv[]){
	
	int fd, fd2, len, i;
	int count = 0;
	int fileLength = 1;
	ssize_t nread;
	char s[1];
	char  word[256];
	char * toComp = "pipe";
	char* ret = malloc(sizeof(char)*256);
	int c = 0;
	
	fd = atoi(argv[1]);
	fd2 = atoi(argv[2]);

	while((nread = read(fd, s, sizeof(s))) > 0)
	{
		word[c] = s[0];
		c++;
		if(s[0] == '\n')
		{
			ret = strstr(word, toComp);
			if(ret != NULL)	
				count++;
			for(i=0;i<=c;i++)
				word[i] = '\0';
			c = 0;
		}
	}
	
	close(fd);
	write(fd2, &count, sizeof(count));
	close(fd2);
	exit(EXIT_SUCCESS);

	return 0;
}
