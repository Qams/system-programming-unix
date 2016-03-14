/*
 * Include copy, copy2, writeall and readall functions
 */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

//#define BUFSIZE 1

void copy(char *from, char *to, const int BUFSIZE)  
{
	int fromfd = -1, tofd = -1;
	ssize_t nread;
	char buf[BUFSIZE];
	
	fromfd = open(from, O_RDONLY);
	if((fromfd == -1) || (errno != 0))
	{
		perror("Brak pliku");
		exit(EXIT_FAILURE);
	}
	tofd = open(to, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR);

	if((tofd == -1))
	{
		if(errno == EACCES)
		{
			perror("Bledne prawa dostepu");
			exit(EXIT_FAILURE);
		}
		perror("Nie udalo sie otworzyc pliku do zapisu");
		exit(EXIT_FAILURE);
	}
	while ((nread = read(fromfd, buf, sizeof(buf))) > 0){
	    	if(write(tofd, buf, nread) == -1)
	 	{
			perror("Blad zapisu");
			exit(EXIT_FAILURE);
		}	
	}
	if(nread == -1)
	{
		perror("Blad odczytu");
		exit(EXIT_FAILURE);
	}
        close(fromfd);
	close(tofd);
	return;
}

void copy2(char *from, char *to)
{
	FILE *stfrom, *stto;
	int c;
	
	if ((stfrom = fopen(from, "r") ) == NULL){}
	if(( stto = fopen(to, "w") ) == NULL) {}
	while ((c = getc(stfrom)) != EOF)
		putc(c, stto);
	fclose(stfrom);
	fclose(stto);
	return;
	
}

ssize_t writeall(int fd, const void *buf, size_t nbyte)
{
	ssize_t nwritten = 0, n;

	do {
		if ((n = write(fd, &((const char *)buf)[nwritten], nbyte - nwritten)) == -1) {
			if (errno == EINTR)
				continue;
			else
				return -1;
		}
		nwritten += n;
	} while (nwritten < nbyte);
	return nwritten;
}

ssize_t readall(int fd, void *buf, size_t nbyte)
{
	ssize_t nr = 0, nread;
	while((nread = read(fd, &((char *)buf)[nr], nbyte - nr)) > 0)
	{
		if(write(1, buf, nread) == -1)
	 	{
			perror("Blad zapisu");
			exit(EXIT_FAILURE);
		}	
		nr += nread;
	}	
	return nr;
}

