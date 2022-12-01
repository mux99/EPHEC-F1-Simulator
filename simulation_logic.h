/* return lenght of given NULL terminated array */
int array_len_1(char* list){
	int len;
	for(len = 0; list[len] != '\0'; len++){}
	return len;
}

struct GrandPrix* init_GPs(char* data, int car_lenght) {
	char** lines = split(data, "\r");
	char** words;
	struct GrandPrix* out;
	int i;
	for(i=0; lines[i] != NULL; i++) {
		words = split(lines[i], ",");
		out[i] = GP_init(i, words[0],atoi(words[1]),atoi(words[2]),car_lenght,false);
	}
	out[i] = GP_init(i,"NULL",50,1,0,true);
	free(lines);
	free(words);
	return out;
}

struct Car* init_CARs(char* data) {
	char** lines = split(data, "\n");
	char** words;
	struct Car* out;
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

void practice(int gp, int len_cars) {
	printf("---practice---\n");
	int i;
	pid_t pid = 0;
	int n = 0;
	for (i=0; i < len_cars; i++) {
		n++;
		pid = fork();
		if (pid > 0) {
			car_sim_practice(i,gp,3600000,0);
			exit(0);
		}
	}
	int status;
	while (n > 0) {
		pid = wait(&status);
		--n;
	}
	printf("---end practice---");
}

void qualifications(int gp, int len_cars) {

}

void sprint(int gp, int len_cars) {

}

void race(int gp, int len_cars) {

}

void weekend1(int gp, int len_cars) {
	printf("---weekend1---\n");
	practice(gp, len_cars);
	qualifications(gp, len_cars);
	race(gp, len_cars);
}

void weekend2(int gp, int len_cars) {
	practice(gp, len_cars);
	qualifications(gp, len_cars);
	sprint(gp, len_cars);
	race(gp, len_cars);
}