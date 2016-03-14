#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "t.h"
#include "defs.h"
 
int main (int argc, char **argv) {
    int f1, c;
    char b[BUFSIZE], *n1;
 
    c = 20;
    n1 = argv[1];
 
	timestart();
    f1 = open (n1, O_RDONLY);
	if(f1 == -1)
	{
		perror("Blad otwarcia pliku");
		printf("STRERROR: %s\n", strerror(2));
		exit(EXIT_FAILURE);
	}
	timestop("Czas odczyt stop!");
    if(read (f1, b, c) == -1)
	{
		perror("Blad odczytu");
		exit(EXIT_FAILURE);
	}
    printf("%s: Przeczytano %d znakow z pliku %s: \"%s\"\n",
	   argv[0], c, n1, b);
	printf("Deskryptor: %d\n", f1);
	printf("ERRNO wysoni: %d\n", errno);
    close(f1);
 
    return(0);
}
