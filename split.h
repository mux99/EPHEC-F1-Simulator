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