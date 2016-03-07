#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <errno.h>
#include <aio.h>
#define KILO 1024
#define BUFSIZE 8
/* -------------------------------------------------------------------------------- */

static void print_type(struct stat *sb);
static void print_ino(const struct stat *sb);
static void print_perms(const struct stat *sb);
static void print_linkc(const struct stat *sb);
static void print_owner(const struct stat *sb);
static void print_size(const struct stat *sb);
static void print_laststch(const struct stat *sb);
static void print_lastacc(const struct stat *sb);
static void print_lastmod(const struct stat *sb);
static void print_name(const struct stat *sb, char *name);
static void print_content(char* name);
void timeConvert(double t);
/* -------------------------------------------------------------------------------- */

int main(int argc, char *argv[])
{
  struct stat sb;
  
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  if (stat(argv[1], &sb) == -1) {
    perror("stat");
    exit(EXIT_SUCCESS);
  }
  
  print_type(&sb);
  print_name(&sb, argv[1]);
  print_ino(&sb);
  print_perms(&sb);
  print_linkc(&sb);
  print_owner(&sb);
  print_size(&sb);
  print_laststch(&sb);
  print_lastacc(&sb);
  print_lastmod(&sb);
  print_content(argv[1]);
  
  exit(EXIT_SUCCESS);
}
/* -------------------------------------------------------------------------------- */

static void print_type(struct stat *sb){
  printf("sb->st_mode: %d\n", sb->st_mode); 
  printf("File type:                ");
  switch (sb->st_mode & S_IFMT) {
  case S_IFBLK:  printf("block device\n"); 				break;
  case S_IFCHR:  printf("character device\n");       	break;
  case S_IFREG:  printf("regular file\n"); 				break;
  case S_IFDIR:  printf("directory\n");               	break;
  case S_IFIFO:  printf("pipe\n");						break;
  case S_IFLNK:  printf("symbolic link\n");           	break;
  case S_IFSOCK:  printf("socket\n");                 	break;

  default:       printf("unknown?\n");                break;
  }
}
/* -------------------------------------------------------------------------------- */

static void print_ino(const struct stat *sb){
  printf("I-node number:            %ld\n", (long) sb->st_ino);
}
/* -------------------------------------------------------------------------------- */

static void print_perms(const struct stat *sb){
  printf("Mode:                     %lo (octal)\n", (unsigned long) sb->st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
  uid_t u = getuid();
  gid_t g = getgid();
  if(sb->st_uid == u)
  {
	printf("USER - ");
	if(sb->st_mode & S_IRUSR)
		printf("Read: yes ");
	else 
		printf("Read: no ");
	if(sb->st_mode & S_IWUSR)
		printf("Write: yes ");
	else
		printf("Write: no ");
	if(sb->st_mode & S_IXUSR)
		printf("Exec: yes \n");
	else
		printf("Exec: no \n");
  }
  else if(sb->st_gid == g)
  {
	printf("GROUP\n");
	if(sb->st_mode & S_IRGRP)
		printf("Read: yes ");
	else 
		printf("Read: no ");
	if(sb->st_mode & S_IWGRP)
		printf("Write: yes ");
	else
		printf("Write: no ");
	if(sb->st_mode & S_IXGRP)
		printf("Exec: yes \n");
	else
		printf("Exec: no \n");
  }
  else
  {
	printf("OTHER\n");
	if(sb->st_mode & S_IROTH)
		printf("Read: yes ");
	else 
		printf("Read: no ");
	if(sb->st_mode & S_IWOTH)
		printf("Write: yes ");
	else
		printf("Write: no ");
	if(sb->st_mode & S_IXOTH)
		printf("Exec: yes \n");
	else
		printf("Exec: no \n");
  }
}
/* -------------------------------------------------------------------------------- */

static void print_linkc(const struct stat *sb){
  printf("Link count:               %ld\n", (long) sb->st_nlink);
}
/* -------------------------------------------------------------------------------- */

static void print_owner(const struct stat *sb){
  struct group *gr = getgrgid(sb->st_gid);
  struct passwd *paswd = getpwuid(sb->st_uid);
  printf("Ownership:                UID=%s(%ld)   GID=%s(%ld)\n", paswd->pw_name, (long) sb->st_uid, gr->gr_name, (long) sb->st_gid);
}
/* -------------------------------------------------------------------------------- */

static void print_size(const struct stat *sb){
  int i=0;
  char* rozmiar; 
  printf("Preferred I/O block size: %ld bytes\n", (long) sb->st_blksize);
  while(1)
  {
	if(sb->st_size > KILO*(i+1))
		i++;
	else
		break;
  }
  switch(i){
	  case 0: rozmiar = "bytes"; break;
	  case 1: rozmiar = "KB"; break; 
	  case 2: rozmiar = "MB"; break;
	  case 3: rozmiar = "GB"; break;
	  case 4: rozmiar = "TB"; break;
	  default: rozmiar = "bytes"; break;
  }
  if(i==0)
	printf("File size:                %lld %s\n",((long long) sb->st_size), rozmiar);
  else
  	printf("File size:                %lld %s\n",((long long) sb->st_size)/KILO*i, rozmiar);
  printf("Blocks allocated:         %lld\n",(long long) sb->st_blocks);
}
/* -------------------------------------------------------------------------------- */

static void print_laststch(const struct stat *sb){
  printf("Last status change:       %s", ctime(&sb->st_ctime));
  printf("Last change: ");
	timeConvert(difftime(time(NULL), sb->st_ctime));
}
/* -------------------------------------------------------------------------------- */

static void print_lastacc(const struct stat *sb){
  printf("Last file access:         %s", ctime(&sb->st_atime));
  //printf("Last file access: %M", sb->st_atime);
	timeConvert(difftime(time(NULL), sb->st_atime));
}
/* -------------------------------------------------------------------------------- */

static void print_lastmod(const struct stat *sb){
  printf("Last file modification:   %s", ctime(&sb->st_mtime));
	printf("Last modification: ");
	timeConvert(difftime(time(NULL), sb->st_mtime));
  
}

/* -------------------------------------------------------------------------------- */

static void print_content(char* name){
	int odp;
	printf("Czy chcesz wypisac zawartosc pliku? [1/0] ");
	scanf("%d", &odp);
	if(odp == 1)
	{
		struct aiocb cb;
		char buf1[BUFSIZE];
		int fd = open(name, O_RDWR);
		if(fd == -1)
		{
			perror("Blad otwarcia");
			exit(EXIT_FAILURE);
		}
		memset(&cb, 0, sizeof(cb));
		cb.aio_fildes = fd;
		cb.aio_buf = buf1;
		cb.aio_nbytes = sizeof(buf1);
		cb.aio_sigevent.sigev_notify = SIGEV_NONE;
		int numBytes;
		do{
			if(aio_read(&cb) == -1)
			{
				perror("Blad odczytu");
				exit(EXIT_FAILURE);
			}
			while(aio_error(&cb) == EINPROGRESS){
				
			}
			printf("%s", buf1);
			memset(buf1, 0, BUFSIZE);
			cb.aio_offset += BUFSIZE;
			
		}
		while(aio_return(&cb)>0);
	}
}
/* -------------------------------------------------------------------------------- */

void timeConvert(double t)
{
	if((t/(3600*24*365))>=1)
		printf("%d year(s) ago\n", (int)t/(3600*24*365));
	else if((t/(3600*24))>=1)
		printf("%d day(s) ago\n", (int)t/(3600*24));
	else if((t/(3600))>=1)
		printf("%d hour(s) ago\n", (int)t/(3600));
	else if((t/60)>=1)
		printf("%d minute(s) ago\n", (int)t/60);
	else 
		printf("%d second(s) ago\n", (int)t);
}

static void print_name(const struct stat *sb, char *name){
  char* bname = basename(name);
  char buf[512];
  printf("Name of the file:         %s\n", bname);
 int id = readlink(name, buf, 512);
  if(id != -1)
  {
	write(1, "Link name: ", 11);
	write(1, name, strlen(name));
	write(1, " -> ", 4);
	write(1, buf, id);
	printf("\n");
  }

}
/* -------------------------------------------------------------------------------- */

