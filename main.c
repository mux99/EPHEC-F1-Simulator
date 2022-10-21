#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

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
int int main(int argc, char const *argv[])
{
	//initialise variables to be shared
	Car* cars = init_CARs(read_CSV("data/cars.csv"));
	GrandPrix* gps = init_GPs(read_CSV("data/grand_prix.csv"));

	//share memory

	return 0;
}