#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>

#include <fcntl.h>     //posix sem
#include <sys/stat.h>  //posix sem
#include <semaphore.h> //posix sem

#define SHM_SIZE 2
#define DATA "/data"
#define SPACE "/space"

static int shmid;
static char *shm_p;
sem_t *data, *space;