#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
//#include <sys/types.h>


#include "struct_CAR.h"
#include "struct_GP.h"
#include "file_interactions.h"
#include "simulation_logic.h"

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
*/

/* ----MAIN----*/
int main(int argc, char const *argv[])
{
	char* cars_file = "date/cars.csv";
	char* gps_file = "date/grand_prix.csv";

	int len_cars = countlines(cars_file);
	int len_gps = countlines(gps_file);
	
	//init cars shared memory
	int shmid_cars = shmget(33,len_cars * sizeof(struct Car), IPC_CREAT | 0666);
	struct Car* cars = shmat(shmid_cars,0,0);

	int shmid_gps = shmget(33,len_gps * sizeof(struct Car), IPC_CREAT | 0666);
	struct GrandPrix* gps = shmat(shmid_gps,0,0);

	//init structs lists
	cars = init_CARs(read_file(cars_file));
	gps = init_GPs(read_file(gps_file),len_cars);

	int i;
	for (i=0; gps[i].is_null != false; i++){
		if (gps[i].weekend_type == 1){
			weekend1(i);
		}
		else if (gps[i].weekend_type == 2){
			weekend2(i);
		}
	}

	return 0;
}