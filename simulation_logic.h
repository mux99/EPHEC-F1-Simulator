/* return lenght of given NULL terminated array */
int array_len_3(char*** list){
	int len;
	for(len = 0; list[len] != NULL; len++){}
	return len;
}

/* return lenght of given NULL terminated array */
int array_len_1(char* list){
	int len;
	for(len = 0; list[len] != '\0'; len++){}
	return len;
}

struct GrandPrix* init_GPs(char*** data) {
	struct GrandPrix* out = malloc(sizeof(struct GrandPrix)*array_len_3(data));
	int i;
	for(i=0; data[i] != NULL; i++) {
		out[i] = GP_init(data[i][0],atoi(data[i][1]),false);
	}
	out[i] = GP_init("NULL",50,true);
	return out;
}

struct Car* init_CARs(char*** data) {
	struct Car* out = malloc(sizeof(struct Car)*array_len_3(data));
	int i;
	for(i=0; data[i] != NULL; i++) {
		out[i] = CAR_init(atoi(data[i][0]),data[i][1],data[i][2],false);
	}
	out[i] = CAR_init(0,"NULL","NULL",true);
	return out;
}

void practice() {

}

void qualifications() {

}

void sprint() {

}

void race() {

}

void weekend1() {
	practice();
	practice();
	practice();

	qualifications();
	qualifications();
	qualifications();

	race();
}

void weekend2() {
	practice();

	qualifications();
	qualifications();
	qualifications();

	practice();

	sprint();

	race();
}