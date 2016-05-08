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
	int f2, i;
	int value;

	pipe(pfd);
	pipe(pfd2);

	int f = fork();
	
	if(f == 0)
	{
		char bufIn[128];
		char bufOut[128];
		char bufIn2[128];
		char bufOut2[128];
		f2 = fork();


		if(f2 == 0)
		{
			snprintf(bufIn2, sizeof(bufIn2), "%d", pfd2[0]);
			snprintf(bufOut, sizeof(bufOut), "%d", pfd[1]);
			execlp("./p2", "p2", bufIn2, bufOut, NULL);
			exit(EXIT_FAILURE);
		}
		snprintf(bufOut2, sizeof(bufOut2), "%d", pfd2[1]);
		close(pfd[1]);
		close(pfd2[0]);
		close(pfd[0]);
		execlp("./p1", "p1", bufOut2, NULL);
		exit(EXIT_FAILURE);
		
	}

	for(i = 0; i<10; i++)
	{
		read(pfd[0], &value, sizeof(int));
		printf("VALUE: %d\n", value);
	}
	
	return 0;
}
