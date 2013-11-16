#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

#define SHMSZ     27

int main()
{
    char input[80];
    int lock = 1;
    int shmid;
    key_t key;
    char *shm;

	printf("***Writer Starting...\n");

    /*key*/
	key   = ftok(".", 's');
    //key = 5678;

    /*
     * Create the segment.
     */
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

	printf("***Writer created shared memory \n");

    /*
     * Now we attach the segment to our data space.
     */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

	printf("***Writer attached to shared memory \n");

    /*
     * Now put some things into the memory for the
     * other process to read.
     */

	printf("Input a string please: \n");
	scanf ("%s", input);
	shm = &input;
	//lock = 1;
	//*shm++ = lock; 

	printf("***Writer wrote %s \n", shm);
	printf("***Writer waiting for Reader... \n");

    while (1)
        sleep(1);

	printf("***Writer exiting \n");

    return 0;
}

