struct GrandPrix {
	bool is_null;

	char* location;
	int track_lenght;
	int sprint_laps_number;
	int race_laps_number;
	int GP_state;
	//the num correspond to the current activity to be displayed.
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
}location, track_lenght, sprint_laps_number, race_laps_number, GP_state;

struct GrandPrix GP_init(char* location, int track_lenght, bool is_null) {
	struct GrandPrix out;
	out.is_null = allocSharedMem(sizeof(bool));
	out.location = allocSharedMem(sizeof(char)*array_len_1(location));
	out.track_lenght = allocSharedMem(sizeof(int));
	out.sprint_laps_number = allocSharedMem(sizeof(int));
	out.race_laps_number = allocSharedMem(sizeof(int));

	out.is_null = is_null;
	out.location = location;
	out.track_lenght = track_lenght;
	out.sprint_laps_number = 100000 / track_lenght;
	out.race_laps_number = 300000 / track_lenght;
	return out;
};