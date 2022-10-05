#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int car_nums[] = {44, 63, 1, 11, 55, 16, 4, 3, 14, 31, 10, 22, 5, 18, 6, 25, 77, 24, 47, 9, NULL};

char* locations[] = {"Bharain", "Saudi Arabian", "Australian", "Emilia Romagna", "Miami", "Spanish", "Monaco", "Azerbaijan", "Canadian", "British", "Austrian", "French", "Hungarian", "Belgian", "Dutch", "Italian", "Singapore", "Japanese", "United States", "Mexico City", "são Paulo", "Abu Dhabi", NULL};

//"class" grand prix (GP)
struct GrandPrix {
	char* location;

	int* practice1;
	int p1_best;

	int* practice2;
	int p2_best;

	int* practice3;
	int p3_best;

	int* qualifications;

	int* race;
};

//une voiture est définie par son numéro est son total de points
struct Car {
	int number;
	int points; //(total)

	int* points_GP; //list of points gained during each GP
	int* best_laps; //list of best lap in order of GP
};

//generate a random time corresponding to the time spent
//traversing 1/3 of a lap
int get_time(int min, int max) {
	return (rand() % (21)) + 25;
};


int length(int*** list) {

}



//=====MAIN=====

//display the given 2D matrix containing strings
//	(first line is collum names)
//	(everything must be NULL terminated)
void display(char*** board) {
	int* lenghts[]
	for (i=0; board[i] != NULL; i++) {
	}
};

void main() {
	//initialise random number generator
	srand(time(0));


	//go through cars numbers to create them
	Cars* cars = malloc(sizeof(Car));
	cars[0] = NULL;
	cars_number = 0;

	for (i=0; cars[i] != NULL; i++) {
		//add car to list
		struct Car cars[i];
		cars_number++;
		cars = realloc(sizeof(Car) * cars_number+1);
		cars[i+1] = NULL;

		//initialize vars;
		cars[i].number = car_nums[i];
		cars[i].points = 0;
	}


	//go through locations to create and run each grand prix
	GrandPrix* grandprix = malloc(sizeof(GrandPrix));
	grandPrix[0] = NULL;
	cup_number = 0;

	for (i=0; locations[i] != NULL; i++) {
		//add cup to list
		struct GrandPrix grandprix[i];
		cup_number++;
		grandprix = realloc(sizeof(GrandPrix) * i+1);
		grandprix[i+1] = NULL;

		//initialize vars
		grandprix[i].location = locations[i];
	}

};

