#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
     
int main(int argc, char *argv[]){

	int pfd[2];
	int pfd2[2];
	char buf[1];
	char word[256];
	int fd, nread;
	int ileLinii, f2, ilePipe;

	pipe(pfd);
	pipe(pfd2);
	int f = fork();
	fd = open("dict.txt", O_RDONLY);
	if(f == 0)
	{
		close(pfd[0]);
		char bufIn[128];
		char bufOut[128];
		char len[128];
		f2 = fork();
		snprintf(bufOut, sizeof(bufOut), "%d", pfd[1]);
		//close(pfd[0]);
		printf("HELLO");
		if(f2 == 0)
		{
			close(pfd2[0]);
			snprintf(bufOut, sizeof(bufOut), "%d", pfd2[1]);
			execlp("./readkey", "readkey", bufOut, "dict.txt", NULL);
			exit(EXIT_FAILURE);
		}
		execlp("./readword", "readword", bufOut, "dict.txt", NULL);
		exit(EXIT_FAILURE);
		
	}
	while((nread = read(fd, buf, 1)) > 0)
	{
		if(strcmp(buf, "\n") == 0)
		{
			memset(word, 0, sizeof(word));
		}
		write(STDOUT_FILENO, buf, 1);
		strcat(word, buf);
	}
	waitpid(f,NULL,0);
	read(pfd[0], &ileLinii, sizeof(ileLinii)); 
	printf("Przeczytano linii: %d\n", ileLinii);
	waitpid(f2,NULL,0);
	read(pfd2[0], &ilePipe, sizeof(ilePipe));
	printf("Przeczytano pipe: %d\n", ilePipe);
	
	return 0;
}
