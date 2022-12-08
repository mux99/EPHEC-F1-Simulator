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

char *cars_file = "data/cars.csv";
char *gps_file = "data/grand_prix.csv";
const float speed = 0.05;
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
// project:
//	simulate a F1 racing championchip
//

// ALL TIMES IN ms
// ALL DISTENCES IN m

//MEMO on int *data:
//
//-0- practice best lap
//-1- practice lap count
//-2- qualifications round 1 best lap
//-3- qualifications round 2 best lap
//-4- qualifications round 3 best lap
//-5- sprint best lap
//-6- race best lap
//-7- race time
//-8-
//-9-
//-10-
//-11- S1 best
//-12- S2 best
//-13- S3 best

/* ----MAIN----*/
int main(int argc, char const *argv[])
{
	printf("---running---\n");

	int len_cars = countlines(cars_file);
	int len_gps = countlines(gps_file);
	int len_data = (len_cars + 1) * 14;

	// init cars shared memory
	int shmid_cars = shmget(shm_key, len_cars * sizeof(struct Car), IPC_CREAT | 0666);
	struct Car *cars = shmat(shmid_cars, NULL, 0);

	int shmid_gps = shmget(shm_key + 1, len_gps * sizeof(struct Car), IPC_CREAT | 0666);
	struct GrandPrix *gps = shmat(shmid_gps, NULL, 0);

	int shmid_data = shmget(shm_key + 2, len_data * sizeof(float), IPC_CREAT | 0666);
	float *data = shmat(shmid_data, NULL, 0);

	// init structs lists
	init_CARs(cars,read_file(cars_file));
	init_GPs(gps,read_file(gps_file), len_cars);

	printf("---init done---\n");
	weekend1(0, len_cars, len_gps, data, cars);
	// for (i=0; gps[i].is_null == false; i++){
	// 	if (gps[i].weekend_type == 1){
	// 		weekend1(i,len_cars, len_gps,data, cars);
	// 	}
	// 	else if (gps[i].weekend_type == 2){
	// 		weekend2(i,len_cars, len_gps,data, cars);
	// 	}
	// }

	shmdt(gps);
	shmctl(shmid_gps,IPC_RMID,0);
	shmdt(cars);
	shmctl(shmid_cars,IPC_RMID,0);
	shmdt(data);
	shmctl(shmid_data,IPC_RMID,0);
	printf("---finished---\n");
	return 0;
}