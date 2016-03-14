#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>  

void tail(char* path, int ilelinii)
{

	char s[256], c;
	int i, fd;
	off_t where;
	int line = 0;
	ssize_t nread;
	
	fd = open(path, O_RDONLY);
	where = lseek(fd, 1, SEEK_END);
	i = sizeof(s) - 1;
	s[i] = '\0';

	do{

		where = lseek(fd, -2, SEEK_CUR);
		switch(read(fd, &c, 1))
		{
			case 1:
				if(c=='\n')
				{
					line++;
    			}	
				if (i <= 0) {
    					errno = E2BIG;
    					/* handle the error */
    				}
    				break;
    			case -1:
    				/* handle the error */
    				break;
    			default: /* impossible */
    				errno = 0;
    				/* handle the error */
		}
	}while((where > 0) && (line <= ilelinii));
	if(where == 0)
			lseek(fd, 0, SEEK_SET);
	while((nread = read(fd, s, i)) > 0)
	{
		write(1, s, nread);
	}
	close(fd);
	return;

}

int main(int argc, char** argv)
{
	if(argc > 2)
	{
		int i;
		int argum = 0;
		for(i=0;i < strlen(argv[2]);i++)
		{
			int tmp = argv[2][i] - '0';
			if((strlen(argv[2])-(i+1))==0)
				argum += tmp*1;
			else
			argum += tmp*(strlen(argv[2])-(i+1))*10;
		}
		tail(argv[1], argum);
	}
	else 
		tail(argv[1], 10);
	return 0;
}
