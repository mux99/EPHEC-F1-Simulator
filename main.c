#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>
//#include <sys/types.h>

char* cars_file = "data/cars.csv";
char* gps_file = "data/grand_prix.csv";
const int speed = 60;
const int end = -1;
int shm_key = 33;

#include "file_interactions.h"
#include "struct_CAR.h"
#include "struct_GP.h"
#include "display.h"
#include "car_sim.h"
#include "simulation_logic.h"

//
//	EPHEC TI-02 OS
//project:
//	simulate a F1 racing championchip 
//

//ALL TIMES IN ms
//ALL DISTENCES IN m

/* ----MAIN----*/
int main(int argc, char const *argv[])
{
	printf("---running---\n");

	int len_cars = countlines(cars_file);
	int len_gps = countlines(gps_file);
	int len_data = (len_cars+1) * 14 * len_gps;

	//init cars shared memory
	int shmid_cars = shmget(shm_key,len_cars * sizeof(struct Car), IPC_CREAT | 0666);
	struct Car* cars = shmat(shmid_cars,0,0);

	int shmid_gps = shmget(shm_key,len_gps * sizeof(struct Car), IPC_CREAT | 0666);
	struct GrandPrix* gps = shmat(shmid_gps,0,0);

	int shmid_data = shmget(shm_key,len_data * sizeof(int), IPC_CREAT | 0666);
	int* data = shmat(shmid_data,0,0);

	int i;
	for (i=0; i < len_data; i++) {
		if ((i%len_cars == 0) && (i > 0)){
			data[i] = end;
		}
		else {
			data[i] = 0;
		}
	}

	//init structs lists
	cars = init_CARs(read_file(cars_file));
	gps = init_GPs(read_file(gps_file),len_cars);

	printf("---init done---\n");
	weekend1(0,len_cars);
	// for (i=0; gps[i].is_null == false; i++){
	// 	if (gps[i].weekend_type == 1){
	// 		weekend1(i,len_cars);
	// 	}
	// 	else if (gps[i].weekend_type == 2){
	// 		weekend2(i,len_cars);
	// 	}
	// }

	shmdt(gps);
	shmdt(cars);
	return 0;
}