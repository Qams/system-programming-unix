#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/resource.h>

#include <stdio.h>

#define BUFSIZE 5

int main(int argc, char* argv[])
{
  struct rlimit limit;
  char buf[BUFSIZE] = {'a','a','a','a','a'};
  char* filename;
  int bytes = 0, towrite, smin = 0, smax = 10000, sdef = 100, 
    wrote, fd, s = sdef; 

	if(argc == 2)
  	filename = argv[1];
	else if(argc > 2){
		filename = argv[2];
		sdef = atoi(argv[1]);
		s = sdef;
	}
	else
	{
		perror("Error input data");
		exit(EXIT_FAILURE);
	}
  if((s < smin) || (s > smax))
     s = sdef;     
  
  if(getrlimit(RLIMIT_FSIZE, &limit) == -1){
		perror("getrlimit ERROR");
		exit(EXIT_FAILURE);
	}

  printf("RLIMIT_FSIZE: cur=%d, max=%d\n", limit.rlim_cur, limit.rlim_max);
  fflush(stdout);

  printf("Writing %d bytes into %s file...\n", s, filename);
  fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC);
  do{
    towrite = s - bytes;
    towrite = towrite<BUFSIZE?towrite:BUFSIZE;
    wrote = write(fd, buf, towrite);
    bytes += wrote;
    if(wrote == -1)
      break;
  }
  while((wrote > 0) && (bytes < s));
  close(fd);

  return 0;
}
