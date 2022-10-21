struct GrandPrix {
	char* location;
	int track_lenght;
	int spint_laps_number;
	int race_laps_number;
	int GP_state = 0; //the num correspond to the current activity to be displayed.
	//depending on the weekend type some states might be skipped

	//in all the lists below, the elements are in the same order as the CAR* list

	//practices, best laps only
	int* practice1; //0
	int* practice2; //1
	int* practice3; //2

	//qualifs
	int* qualifications_1_laps; //3
	int* qualifications_1_time;
	int* qualifications_1_best_lap;

	int* qualifications_2_laps; //4
	int* qualifications_2_time;
	int* qualifications_2_best_lap;

	int* qualifications_3_laps; //5
	int* qualifications_3_time;
	int* qualifications_3_best_lap;

	//sprint
	int* sprint_laps; //6
	int* sprint_time;
	int* sprint_best_lap;

	//race
	int* race_start_grid; //index of cars in CAR* in start order
	int* race_laps; //7
	int* race_time;
	int* race_best_lap;
};

GrandPrix GP__init(char* location, int track_lenght) {
	GrandPrix out;
	out = { .location = location, .track_lenght = track_lenght};
	out.sprint_laps_number = 100000 / track_lenght;
	out.race_laps_number = 300000 / track_lenght;
};