/* return lenght of given NULL terminated array */
int array_len_1(char* list){
	int len;
	for(len = 0; list[len] != '\0'; len++){}
	return len;
}

int get_time() {
	return rand() % ( + 1 - 25000) + 25000;
};

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

void practice(int curent_gp) {
	int i;
	for (i=0; cars[i].is_null != false; i++){
		
	}
}

void qualifications(int curent_gp) {

}

void sprint(int curent_gp) {

}

void race(int curent_gp) {

}

void weekend1(int curent_gp) {
	practice(curent_gp);
	qualifications(curent_gp);
	race(curent_gp);
}

void weekend2(int curent_gp) {
	practice(curent_gp);
	qualifications(curent_gp);
	sprint(curent_gp);
	race(curent_gp);
}