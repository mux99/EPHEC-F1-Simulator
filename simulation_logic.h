/* return lenght of given NULL terminated array */
int array_len_1(char* list){
	int len;
	for(len = 0; list[len] != '\0'; len++){}
	return len;
}

struct GrandPrix* init_GPs(char* data, int car_lenght) {
	char** lines = split(data, "\r");
	char** words;
	struct GrandPrix* out = malloc(array_len_2(lines) * sizeof(struct GrandPrix));
	int i;
	for(i=0; lines[i] != NULL; i++) {
		words = split(lines[i], ",");
		out[i] = GP_init(words[0],atoi(words[1]),atoi(words[2]),car_lenght,false);
	}
	out[i] = GP_init("NULL",50,1,0,true);
	free(lines);
	free(words);
	return out;
}

struct Car* init_CARs(char* data) {
	char** lines = split(data, "\n");
	char** words;
	struct Car* out = calloc(array_len_2(lines), sizeof(struct Car));
	int i;
	for(i=0; lines[i] != NULL; i++) {
		words = split(lines[i], ",");
		out[i] = CAR_init(atoi(words[0]),words[1],words[2],false);
	}
	out[i] = CAR_init(0,"NULL","NULL",true);
	free(lines);
	free(words);
	return out;
}

void practice(struct GrandPrix gp, struct Car* cars) {
	printf("---practice---\n");
	int i;
	int pid = 0;
	for (i=0; cars[i].is_null != false; i++) {
		pid = fork();
		if (pid == 0){
			car_sim_practice(i,gp,cars,3600000,0);
			break;
		}
	}
	if (pid > 0) {
		printf("main\n");
	}
}

void qualifications(struct GrandPrix gp, struct Car* cars) {

}

void sprint(struct GrandPrix gp, struct Car* cars) {

}

void race(struct GrandPrix gp, struct Car* cars) {

}

void weekend1(struct GrandPrix gp, struct Car* cars) {
	practice(gp, cars);
	qualifications(gp, cars);
	race(gp, cars);
}

void weekend2(struct GrandPrix gp, struct Car* cars) {
	practice(gp, cars);
	qualifications(gp, cars);
	sprint(gp, cars);
	race(gp, cars);
}