#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUFSIZE 1024

void cat(int argc, char* file)
{
	char buf[BUFSIZE];
	ssize_t nread;
	int fromfd = -1;

	if(argc == 2)
	{
		fromfd = open(file, O_RDONLY);
		if(fromfd == -1)
		{
			perror("Blad otwarcia pliku");
			exit(EXIT_FAILURE);
		}
		while((nread = read(fromfd, buf, sizeof(buf)+1))>0)
			write(1, buf, nread);

		close(fromfd);
	}
	else if(argc == 1)
	{
		while(1)
		{
			nread = read(0, buf, sizeof(buf)+1);
			if(nread == -1)
			{
				perror("Blad odczytu");
				exit(EXIT_FAILURE);
			}
			if((write(1, buf, nread)) == -1)
			{
				perror("Blad zapisu");
				exit(EXIT_FAILURE);
			}
				
		}
	}

}

int main(int argc, char **argv)
{
	if(argc > 2)
	{
		fprintf(stderr,"usage: %s from_pathname to_pathname\n", argv[0]);
		return 1;
	}
	cat(argc, argv[1]);
	return 0;
}
