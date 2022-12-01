struct GrandPrix {
	bool is_null;

	char* location;
	int track_lenght;
	int sprint_laps_number;
	int race_laps_number;
	int weekend_type;
	int GP_state;
	//the num correspond to the current activity to be displayed.
	//depending on the weekend type some states might be skipped

	//in all the lists below, the elements are in the same order as the CAR* list

	//practices, best laps only
	int practice; //0

	//qualifs
	int qualif_1_laps; //1
	int qualif_1_best_lap;

	int qualif_2_laps; //2
	int qualif_2_best_lap;

	int qualif_3_laps; //3
	int qualif_3_best_lap;

	//sprint
	int sprint_laps; //4
	int sprint_time;
	int sprint_best_lap;

	//race
	int race_start_grid; //index of cars in CAR* in start order
	int race_laps; //5
	int race_time;
	int race_best_lap;
}location, track_lenght, sprint_laps_number, race_laps_number, GP_state;

struct GrandPrix GP_init(int i, char* location, int track_lenght, int weekend_type, int car_lenght, bool is_null) {
	struct GrandPrix out;
	out.is_null = is_null;
	out.location = location;
	out.track_lenght = track_lenght;
	out.weekend_type = weekend_type;
	out.sprint_laps_number = 100000 / track_lenght;
	out.race_laps_number = 300000 / track_lenght;

	if (car_lenght > 0) {
		int offset = i * 14 * (car_lenght+1);
		out.practice = offset;
		out.qualif_1_laps = offset+car_lenght+2;
		out.qualif_1_best_lap = offset+car_lenght+3;
		out.qualif_2_laps = offset+car_lenght+4;
		out.qualif_2_best_lap = offset+car_lenght+5;
		out.qualif_3_laps = offset+car_lenght+6;
		out.qualif_3_best_lap = offset+car_lenght+7;
		out.sprint_laps = offset+car_lenght+8;
		out.sprint_time = offset+car_lenght+9;
		out.sprint_best_lap = offset+car_lenght+10;
		out.race_start_grid = offset+car_lenght+11;
		out.race_laps = offset+car_lenght+12;
		out.race_time = offset+car_lenght+13;
		out.race_best_lap = offset+car_lenght+14;
	}
	return out;
};