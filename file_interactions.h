/* count quotes, true if odd number */
int in_string(char* str){
	int i = 0;
	int n = 0;
	for(i=0; str[i] != '\0'; i++){
		if(str[i] == '"'){
			n++;
		}
	}
	return n % 2 != 0;
}


/* Split string on delim character*/
/* into NULL terminated array */
char** split(char* s, const char delim){
	char** out = malloc(sizeof(char*));
	char tmp2[strlen(s)];
	int len = 1;
	bool inside = false;
	char separator[2]; separator[0] = delim; separator[1] = '\0';

	//split
	char* tmp = strtok(s,&delim);
	while(tmp != NULL){
		//concat end
		if(inside && in_string(tmp)){
			strcat(tmp2, separator);
			strcat(tmp2, tmp);
			inside = false;

			out[len-1] = malloc(sizeof(char) * strlen(tmp2));
			strcpy(out[len-1],tmp2);
			len++;
			out = realloc(out,sizeof(char* ) * len);
		}
		//concat mid
		else if(inside){
			strcat(tmp2, separator);
			strcat(tmp2, tmp);
		}
		//concat start
		else if(in_string(tmp)){
			inside = true;
			strcpy(tmp2, tmp);
		}
		//no concat
		else{
			out[len-1] = malloc(sizeof(char) * strlen(tmp)+1);
			strcpy(out[len-1],tmp);
			len++;
			out = realloc(out,sizeof(char* ) * len);
		}
		tmp = strtok(NULL,&delim);
	}
	out[len-1] = NULL;
	return out;
}

/* return lenght of given NULL terminated array */
int array_len_2(char** list){
	int len;
	for(len = 0; list[len] != NULL; len++){}
	return len;
}

/* Read File to string */
char* read_file(char* path){
	int file = open(path, O_RDONLY);
	if(file<0){printf("error file not found");exit(-1);}

	//get file length
	struct stat stt;
	stat(path,&stt);
	int file_len = stt.st_size;

	//initialize out w/ correct length
	char* out = malloc((file_len +1) * sizeof(char));
	char tmp[file_len + 1];

	//read file to tmp
	read(file,&tmp,file_len);
	close(file);

	//fill 'out'
	tmp[file_len] = '\0';
	strcpy(out, tmp);
	return out;
}

/* Print char[][] NULL terminated */
void print_array(char** a){
	int i;
	printf("\n");
	for(i=0; a[i] != NULL; i++){
		printf("%s",a[i]);
	}
	printf("\n");
}

/* read given csv file*/
/* lines begining by # are comments */
/* into NULL terminated arrays */
char*** read_CSV(char* path) {
	char* tmp = read_file(path);
	char** tmp2 = split(tmp, '\n'); //separate each line of file
	char*** out;

	out = calloc(array_len_2(tmp2), sizeof(char**));

	int i; int j;
	for(i=0; tmp2[i] != NULL; i++) {
		//ignore comments
		if(tmp2[i][0] == '#'){continue;}

		//split line in words
		char** tmp3 = split(tmp2[i], ',');
		out[i] = calloc(array_len_2(tmp3), sizeof(char*));
		int max_j = array_len_2(tmp3);
		
		for(j=0; j < max_j; j++) {
			printf("%s\n", tmp3[j]);
			out[i][j] = calloc(20, sizeof(char));
			out[i][j] = tmp3[j];
		} 
	}
	return out;
}

/* read option file */
/* lines begining by # are comments */
void read_options(char* path) {
	//---TBD---
}