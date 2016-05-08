#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
     
int main(int argc, char *argv[]){
     
	int pfd[2];
	size_t nread;
	char buf[100];
     
	pipe(pfd);
	char * str ="Ur beautiful pipe example";

	long v = fpathconf(pfd[0], _PC_PIPE_BUF);
	if(v == -1)
	{
		printf("No limit for PIPE_BUF\n");
	}
	else{
		printf("Pipe buf: %ld\n", v); 
	}

	int f = fork();	
	if(f == 0){
		int c = close(pfd[1]);
		snprintf(buf, sizeof(buf), "%d", pfd[0]);
		execlp("./piperead", "piperead", buf, NULL);
		exit(EXIT_FAILURE);
	}
	else{
		close(pfd[0]);
		if(write(pfd[1], str, strlen(str)+1) != -1)
			wait(NULL);
		else
			exit(EXIT_FAILURE);
		close(pfd[1]);

	}
     
	return 0;
}


