#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 512

void generujZnaki(int fd2, int ile)
{
	int i=0, l;
	char z;
	for(i;i<ile;i++)
	{
		l = rand()%26;
		z = l + 'a';
		write(fd2, &z, sizeof(z));
	}

}

void pomin(int fd, int ile)
{
	int i = 0; 
	char tmp;

	for(i;i<ile;i++)
	{
		read(fd, &tmp, 1);
	}
}

void szyfruj(char* from, char* to)
{
	int fd, fd2, liczba;
	char c, tmp;
	ssize_t nread, n;

	fd = open(from, O_RDONLY);
	fd2 = open(to, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR);
	
	while((nread = read(fd, &c, 1)) > 0)
	{
		if((n = write(fd2, &c, nread)) == -1)
		{
			perror("Blad zapisu 1");
			exit(EXIT_FAILURE);
		}

		liczba = rand()%9 + 1;
		tmp = liczba + '0';
		if((n = write(fd2, &tmp, 1)) == -1)	
		{
			perror("Blad zapisu 2");
			exit(EXIT_FAILURE);
		}
		generujZnaki(fd2, liczba);
	}
	printf("\n");
	close(fd);
	close(fd2);
}

void deszyfruj(char* from, char* to)
{
	int fd, fd2, liczba, toInt;
	char c, tmp;
	ssize_t nread, n;
	fd = open(from, O_RDONLY);
	fd2 = open(to, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR);
	
	while((nread = read(fd, &c, 1)) > 0)
	{
		if((n = write(fd2, &c, 1)) == -1)	
		{
			perror("Blad zapisu przy deszyfracji");
			exit(EXIT_FAILURE);
		}
		read(fd, &c, 1);
		toInt = c - '0';
		pomin(fd, toInt);
		
	}
}


int main(int argc, char** argv)
{
	szyfruj(argv[1], argv[2]);
	srand(time(NULL));
	return 0;
}
