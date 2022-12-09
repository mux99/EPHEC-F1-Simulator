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
char** split(char* s, char* delim){
	char** out = malloc(sizeof(char*));
	int len = 1;
	//split
	char* tmp = strtok(s,delim);
	while(tmp != NULL){
		out[len-1] = calloc(strlen(tmp)+1, sizeof(char));
		out[len-1] = tmp;
		len++;
		out = realloc(out,sizeof(char* ) * len);
		tmp = strtok(NULL,delim);
	}
	out[len-1] = NULL;
	return out;
}

//DOWLOADED https://stackoverflow.com/questions/12733105/c-function-that-counts-lines-in-file
int countlines(char *filename)
{
  // count the number of lines in the file called filename                                    
  FILE *fp = fopen(filename,"r");
  int ch=0;
  int lines=0;

  if (fp == NULL) {return 0;}

  lines++;
  while ((ch = fgetc(fp)) != EOF)
    {
      if (ch == '\n')
    lines++;
    }
  fclose(fp);
  return lines;
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

void write_file(char* path, char* content)
{
	int fd = open(path, O_WRONLY | O_CREAT, 0644);
	if (fd != -1)
	{
		write(fd, content, strlen(content));
		close(fd);
	}
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