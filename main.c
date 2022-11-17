#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
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
int get_time() {
	return rand() % ( + 1 - 25000) + 25000;
};*/

/* ----MAIN----*/
int main(int argc, char const *argv[])
{
	//1
	printf("%s\n", "1");
	struct Car* cars = init_CARs(read_file("data/cars.csv")); //retourne une liste de struct

	//2
	printf("%s\n", "2");
	struct GrandPrix* gps = init_GPs(read_file("data/grand_prix.csv")); //retourne une liste de struct

	printf("%s\n", "3");

	return 0;
}