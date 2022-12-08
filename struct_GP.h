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
	// 0 practice
	// 1 qualif 1
	// 2 qualif 2
	// 3 qualif 3
	// 4 sprint
	// 5 race
	// any other [end display]

}location, track_lenght, sprint_laps_number, race_laps_number, GP_state;

struct GrandPrix GP_init(int i, char* location, int track_lenght, int weekend_type, int car_lenght, bool is_null) {
	struct GrandPrix out;
	out.is_null = is_null;
	out.location = location;
	out.track_lenght = track_lenght;
	out.weekend_type = weekend_type;
	out.sprint_laps_number = 100000 / track_lenght;
	out.race_laps_number = 300000 / track_lenght;
	out.GP_state = 0;
	return out;
};