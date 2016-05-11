#include <stdio.h>    
#include <stdlib.h>    
#include <sys/types.h>
#include <sys/shm.h>
#include <errno.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>

int main (int argc, char **argv){
	int i;
    key_t shmkey;
    int shmid;
	sem_t *semFive;
    pid_t pid;
    int *p;
	int leftOrRight;
	int flag = 0;
	int myP;
	unsigned int n = 23;
	unsigned int valueFive = 5;

	srand(time(NULL));
    // shared memory
    shmkey = ftok ("/dev/null", 5);      
    printf ("shmkey for p = %d\n", shmkey);
    shmid = shmget (shmkey, sizeof (int), 0644 | IPC_CREAT);
    if (shmid < 0){                        
        perror ("shmget\n");
        exit (1);
    }

	p = (int *) shmat (shmid, NULL, 0);
    *p = 0; 
	semFive = sem_open("tSem", O_CREAT | O_EXCL, 0644, valueFive);      
	sem_unlink("tSem");
    printf ("Semaphores initialized.\n\n");

	for (i = 0; i < n; i++){
        pid = fork ();
		leftOrRight = rand()%2;
		if((i == 0) && (pid == 0))
			*p = leftOrRight;
        if (pid < 0)      
            printf ("Fork error.\n");
        else if (pid == 0)
            break;
    }

	//parent process

	if (pid != 0){
        // wait for all of your kids
        while (pid = waitpid (-1, NULL, 0)){
            if (errno == ECHILD)
                break;
        }

        printf ("\nParent: All of orangutans crossed through the rope.\n");

        shmdt (p);
        shmctl (shmid, IPC_RMID, 0);

        // destroy semaphore
		sem_destroy(semFive);
        exit (0);
    }
	// kids process
	else{
			while(leftOrRight != *p)
			{
			}
			sem_wait(semFive);
			myP = *p;
		    printf ("  Orangutan(%d) is on the rope.\n", i);
			// time, when orangutan is on the line
			sleep (2);
			// 0 - orangutan crossed from left side of line to right
			// 1 - orangutan crossed from right side of line to left
			printf("Orangutan(%d) crossed - left[0] or right[1] side: %d\n" ,i, leftOrRight);
			sem_post(semFive);
			sem_getvalue(semFive, &flag);
			if(flag == valueFive)
				*p = leftOrRight^1;
		     		
		    exit (0);
    }
}

