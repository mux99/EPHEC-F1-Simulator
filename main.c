#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "struct_CAR.h"
#include "struct_GP.h"
#include "simulation_logic.h"
#include "file_interactions.h"

//ALL TIMES IN ms
//ALL DISTENCES IN m

/*
int maxArray(int* array){
    int max = 0;
    for(int i = 0; array[i] != NULL; i++){
        if(array[i] > max){
            max = array[i];
        }
    }
    return max;
}
int get_time() {
	return rand() % ( + 1 - 25000) + 25000;
};*/

/* ----MAIN----*/
int main(int argc, char const *argv[])
{
	int key_1 = 77;
	int key_2 = 78;

	char*** data1 = read_CSV("data/cars.csv");
	char*** data2 = read_CSV("data/grand_prix.csv");

	//share memory
	int shmid_cars = shmget(key_1,sizeof(struct Car)*array_len_3(data1),IPC_CREAT);
	int shmid_gps = shmget(key_2,sizeof(struct GrandPrix)*array_len_3(data2),IPC_CREAT);

	struct Car* cars = shmat(shmid_cars,0,0);
	struct GrandPrix* gps = shmat(shmid_gps,0,0);

	cars = init_CARs(data1);
	gps = init_GPs(data2);
	
	return 0;
}