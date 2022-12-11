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

/* Read File to string */
char* read_file(char* path){
	int file = open(path, O_RDONLY);
	if(file<0){printf("error file not found");exit(-1);}

	//get file length
	struct stat stt;
	stat(path,&stt);
	int file_len = stt.st_size;

	//initialize out w/ correct length
	char* out = calloc(file_len +1, sizeof(char));
	char tmp[file_len + 1];

	//read file to tmp
	read(file,&tmp,file_len);
	close(file);

	//fill 'out'
	tmp[file_len] = '\0';
	strcpy(out, tmp);
	return out;
}

void save_data(struct GrandPrix* gps, struct Car* cars, float* data, int gp, int step, int len_cars)
{
	printf("enter the name of the file:");
	char input[100];
	scanf("%s",input);
	char temp;
	int p[2];
	pid_t pid;
	int status;
	pipe(p);
	fflush(stdout);
	int file = 0;
	if((pid=fork())==0){
		dup2(p[1], 1);
		switch (step)
		{
		case 1:
			scoreboard_practice(len_cars,cars,data,gps[gp],0,0);
			break;

		case 2:
			scoreboard_qualif_1(len_cars,cars,data,gps[gp],0,0);
			break;

		case 3:
			scoreboard_qualif_2(len_cars,cars,data,gps[gp],0,0);
			break;

		case 4:
			scoreboard_qualif_3(len_cars,cars,data,gps[gp],0,0);
			break;

		case 5:
			scoreboard_sprint(len_cars,cars,data,gps[gp],0,0);
			break;

		case 6:
			scoreboard_race(len_cars,cars,data,gps[gp],0,0);
			break;

		case 7:
			scoreboard_recap(len_cars,cars,data,gps[gp]);
			break;
		
		default:
			break;
    	}
		exit(0);
	}
	waitpid(pid,&status,0); //wait for all childs to end
	close(p[1]);

	file = open(input, O_TRUNC | O_CREAT | O_WRONLY, 0666);
	//file = open("output.txt", O_APPEND | O_CREAT | O_WRONLY, 0666);
	while(read(p[0], &temp, 1) > 0){
		write(file, &temp, 1);
	}
	close(file);
}

//does not work well, troubles with triple pointer array 
/* read given csv file*/
/* lines begining by # are comments */
/* into NULL terminated arrays */
/* REMOVED -- bad use of char*** found another way
char*** read_CSV(char* path) {
	char* file = read_file(path);
	char** lines = split(file, '\n'); //separate each line of file
	free(file);
	char*** data;

	data = calloc(((array_len_2(lines))+1)*4*40, sizeof(char));

	int i; int j;
	for(i=0; lines[i] != NULL; i++) {
		//ignore comments
		if(lines[i][0] == '#'){continue;}

		//split line in words
		char** words = split(lines[i], ',');
		//data[i] = calloc(array_len_2(words), sizeof(char*));
		int max_j = array_len_2(words);
		
		for(j=0; words[j] != NULL; j++) {
			//data[i][j] = calloc(40, sizeof(char));
			strcpy(data[i][j],words[j]);
		}
		data[i][j] = NULL;

		free(words);
	}
	data[i] = NULL;
	free(lines);
	return data;
}*/