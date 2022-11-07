#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

/* ----MAIN----*/
int main(int argc, char const *argv[])
{
	int key_1 = 77;
	int key_2 = 78;

	//share memory
	int shmid_cars = shmget(key_1,sizeof(cars),IPC_CREAT);
	int shmid_gps = shmget(key_2,sizeof(gps),IPC_CREAT);
}