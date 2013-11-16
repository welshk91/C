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
	char *input;
    int lock = 1;
    int shmid;
    key_t key;
    char *shm;

    /*key*/
	key   = ftok(".", 's');
    //key = 5678;

    /*
     * Locate the segment.
     */
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

	printf("***Reader located shared memory \n");

    /*
     * Now we attach the segment to our data space.
     */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

	printf("***Reader attached to shared memory \n");

    /*Now read what the server put in the memory.*/

	input = shm;
	//lock = *shm++;	

	printf("***Reader read %s from shared memory \n", input);	 

    return 0;
}
