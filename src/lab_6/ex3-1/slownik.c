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
	int pfd3[2];
	int pfd4[2];

	char buf[1];
	char word[256];
	int fd, nread;
	int ileLinii = 0, f2, ilePipe = 0;

	pipe(pfd);
	pipe(pfd2);
	pipe(pfd3);
	pipe(pfd4);
	int f = fork();
	if(f == 0)
	{
		char bufIn[128];
		char bufOut[128];
		char len[128];
		f2 = fork();
		if(f2 == 0)
		{
			close(pfd[0]);
			close(pfd[1]);
			close(pfd2[1]);
			close(pfd3[0]);
			close(pfd3[1]);
			close(pfd4[0]);
			snprintf(bufIn, sizeof(bufIn), "%d", pfd2[0]);
			snprintf(bufOut, sizeof(bufOut), "%d", pfd4[1]);
			execlp("./readkey", "readkey", bufIn, bufOut, NULL);
			exit(EXIT_FAILURE);
		}
		close(pfd2[0]);
		close(pfd2[1]);
		close(pfd[1]);
		close(pfd3[0]);
		close(pfd4[0]);
		close(pfd4[1]);
		snprintf(bufIn, sizeof(bufIn),  "%d", pfd[0]);
		snprintf(bufOut, sizeof(bufOut), "%d", pfd3[1]);
		execlp("./readword", "readword", bufIn, bufOut,  NULL);
		exit(EXIT_FAILURE);
		
	}
	fd = open("dict.txt", O_RDONLY);
	
	close(pfd3[1]);
	close(pfd4[1]);
	while((nread = read(fd, buf, sizeof(buf))) > 0)
	{
		write(STDOUT_FILENO, buf, 1);
		write(pfd[1], buf, 1);
		write(pfd2[1], buf, 1);
	}
	close(fd);
	close(pfd[1]);
	close(pfd2[1]);
	close(pfd[0]);
	close(pfd2[0]);
	waitpid(f,NULL,0);
	read(pfd3[0], &ileLinii, sizeof(ileLinii)); 
	printf("Przeczytano linii: %d\n", ileLinii);
	waitpid(f2,NULL,0);
	read(pfd4[0], &ilePipe, sizeof(ilePipe));
	printf("Przeczytano pipe: %d\n", ilePipe);
	close(pfd3[0]);
	close(pfd4[0]);
	
	return 0;
}
