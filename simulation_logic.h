/* return lenght of given NULL terminated array */
int array_len(char*** list){
	int len;
	for(len = 0; list[len] != NULL; len++){}
	return len;
}


GrandPrix* init_GPs(char*** data) {
	GrandPrix* out = malloc(sizeof(GrandPrix)*array_len(data));
	int i;
	for(i=0; data[i] != NULL; i++) {
		out[i] = GP_init(data[i][0],atoi(data[i][1]))
	}
}

Car* init_CARs(char*** data) {
	Car* out = malloc(sizeof(GrandPrix)*array_len(data));
	int i;
	for(i=0; data[i] != NULL; i++) {
		out[i] = CAR_init(atoi(data[i][0]),data[i][1],data[i][2])
	}
}

void weekend1() {
	practice(cars);
	practice(cars);
	practice(cars);

	qualifications(cars, 1080000);
	qualifications(cars, 900000);
	qualifications(cars, 720000);

	race(cars, grandprix.race_laps);
}

void weekend2() {
	practice(cars);

	qualifications(cars, 1080000);
	qualifications(cars, 900000);
	qualifications(cars, 720000);

	practice(cars);

	sprint(cars, grandprix.sprint_laps_number);

	race(cars, grandprix.race_laps);
}