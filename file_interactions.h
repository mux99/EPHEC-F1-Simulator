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

/* Print char[][] NULL terminated */
void print_array(char** a){
	int i;
	printf("\n");
	for(i=0; a[i] != NULL; i++){
		printf("%s\n",a[i]);
	}
	printf("NULL\n");
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

/* read given csv file*/
/* lines begining by # are comments */
/* into NULL terminated arrays */
char*** read_CSV(char* path) {
	char* file = read_file(path);
	char** lines = split(file, '\n'); //separate each line of file
	free(file);
	char*** data;

	data = calloc(array_len_2(lines), sizeof(char**));

	int i; int j;
	for(i=0; lines[i] != NULL; i++) {
		//ignore comments
		if(lines[i][0] == '#'){continue;}

		//split line in words
		char** words = split(lines[i], ',');
		data[i] = calloc(array_len_2(words), sizeof(char*));
		int max_j = array_len_2(words);
		
		for(j=0; words[j] != NULL; j++) {
			data[i][j] = calloc(40, sizeof(char));
			strcpy(data[i][j],words[j]);
		}
		data[i][j] = NULL;

		free(words);
	}
	data[i] = NULL;
	free(lines);
	return data;
}

/* read option file */
/* lines begining by # are comments */
void read_options(char* path) {
	//---TBD---
}