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

struct GrandPrix* init_GPs(char* data) {
	char** lines = split(data, "\r");
	char** words;
	struct GrandPrix* out = malloc(array_len_2(lines) * sizeof(struct GrandPrix));
	int i;
	for(i=0; lines[i] != NULL; i++) {
		words = split(lines[i], ",");
		out[i] = GP_init(words[0],atoi(words[1]),false);
	}
	out[i] = GP_init("NULL",50,true);
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

void practice() {
//set shared memory
	//share one best lap + best of each zone
	//share end flag (sémaphores?)
//call each subporcess (fork?)
//detect end of parctice
//wait for user input
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