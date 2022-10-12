#include <time.h>
#include <stdlib.h>
#include <stdio.h>

//ALL STORED TIMES IN ms
//ALL STORED LENGTH IN m

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
int get_time() {
	return rand() % ( + 1 - 25000) + 25000;
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

void weekend1(GrandPrix grandprix, Car* cars) {
	int race_laps = 350000 / grandprix.track_lenght;

	practice(cars);
	practice(cars);
	practice(cars);

	qualifications(cars, 1080000);
	qualifications(cars, 900000);
	qualifications(cars, 720000);

	race(cars, race_laps)
}

void weekend2(GrandPrix grandprix, Car* cars) {
	int race_laps = 350000 / grandprix.track_lenght;
	int sprint_laps = 100000 / grandprix.track_lenght;

	practice(cars);

	qualifications(cars, 1080000);
	qualifications(cars, 900000);
	qualifications(cars, 720000);

	practice(cars);

	sprint(cars, sprint_laps);

	race(cars, race_laps);
}

int** practice(Car* cars) {
	int i;
/*	int** best_laps = (int **) malloc(len1(cars)*sizeof(int)*4)

	for (i=0; cars[i] != NULL; i++) {
		int tot_time = 0;
		best_laps[i] = 0;
		while (tot_time < 3600) {
			int tmp = get_time()+get_time()+get_time();
			if ((tot_time+tmp) > 3600) {
				break;
			}
			if (tmp > best_laps[i]) {
				best_laps[i] = tmp;
			}
		}
	}
	best_laps[i] = NULL;
	return best_laps;*/
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

