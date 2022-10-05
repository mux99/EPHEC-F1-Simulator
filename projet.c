#include <time.h>
#include <stdlib.h>
#include <stdio.h>

//ALL STORED TIMES IN ms
//ALL STORED LENGTH IN Km

int car_nums[] = {44, 63, 1, 11, 55, 16, 4, 3, 14, 31, 10, 22, 5, 18, 6, 25, 77, 24, 47, 9, NULL};

char* locations[] = {"Bharain", "Saudi Arabian", "Australian", "Emilia Romagna", "Miami", "Spanish", "Monaco", "Azerbaijan", "Canadian", "British", "Austrian", "French", "Hungarian", "Belgian", "Dutch", "Italian", "Singapore", "Japanese", "United States", "Mexico City", "são Paulo", "Abu Dhabi", NULL};

struct GrandPrix {
	char* location;
	int track_lenght = 5;

	int* practice1;
	int p1_best;

	int* practice2;
	int p2_best;

	int* practice3;
	int p3_best;

	int* qualifications;

	int* race;
};

struct Car {
	int number;
	int points; //(total)

	int* points_GP; //list of points gained during each GP
	int* best_laps; //list of best lap in order of GP
};


//====GENERAL====

//generate a random time corresponding to the time spent
//traversing 1/3 of a lap
int get_time(int min, int max) {
	return (rand() % (21)) + 25;
};


int len1(int* list) {
	int i;
	for (i=0; list[i] != NULL; i++);
	return i
}
int len2(int** list) {
	int i;
	for (i=0; list[i] != NULL; i++);
	return i
}
int len3(int*** list) {
	int i;
	for (i=0; list[i] != NULL; i++);
	return i
}

//=====RACES SYM====

char*** weekend1(GrandPrix grandprix, Car* cars) {
	int race_laps = 350 / grandprix.track_lenght;

	tryout(cars);
	tryout(cars);
	tryout(cars);

	qualifications(cars, 18);
	qualifications(cars, 15);
	qualifications(cars, 12);

	race(cars, race_laps)
}

char*** weekend2(char* country, Car* cars) {
	int race_laps = 350 / grandprix.track_lenght;
	int sprint_laps = 100 / grandprix.track_lenght;

	tryout(cars);

	qualifications(cars, 18);
	qualifications(cars, 15);
	qualifications(cars, 12);

	tryout(cars);

	sprint(cars, sprint_laps);

	race(cars, race_laps);
}

int* tryout(Car* cars) {
	int* best_laps[len1(cars)];

	for (int i=0; cars[i] != NULL; i++) {

	}
}

int* qualifications(Car* cars, int duration) {

}

int* sprint(Car* cars, int laps) {

}

int* race(Car* cars, int laps) {

}

	tryout(cars);
	tryout(cars);
	tryout(cars);

	qualifications(cars, 18);
	qualifications(cars, 15);
	qualifications(cars, 12);

	race(cars,race_laps);
}

char*** weekend2(GrandPrix grandprix, Car* cars) {
	int race_laps = 350 / grandprix.track_lenght;
	int sprint_laps = 100 / grandprix.track_lenght;

	tryout(cars);

	qualifications(cars, 18);
	qualifications(cars, 15);
	qualifications(cars, 12);

	tryout(cars);

	sprint(cars,sprint_laps);

	race(cars,race_laps);
}

int* tryout(Car* cars) {

}

int* qualifications(Car* cars, int duration) {

}

int* sprint(Car* cars, int laps) {

}

int* race(Car* cars, int laps) {

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
	Car* cars = malloc(sizeof(Car));
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

