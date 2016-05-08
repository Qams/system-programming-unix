#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void)
{
        int     pfd[2];
        pid_t   pid;
        char    string[] = "Test";
        char    buf[10];

        if(pipe(pfd) == -1)
		{
			perror("PIPE blad");
			exit(EXIT_FAILURE);
		}
        pid = fork();

        if(pid == 0) {
		//close(0);              
 		dup2(pfd[0],0);
        	read(STDIN_FILENO, buf, sizeof(buf));
                printf("Wypisuje: %s", buf);
				close(pfd[1]);
				close(pfd[0]);
        } else {
			close(pfd[0]);
        	write(pfd[1], string, (strlen(string)+1));    
			close(pfd[1]);    
	}

        return 0;
}
