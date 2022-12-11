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

int countlines(char *filename)
{
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("Error: unable to open file %s\n", filename);
    return 1;
  }

  // Count the number of lines
  int count = 0;
  char line[1024];
  while (fgets(line, sizeof(line), file)) {
    if (line[0] != '#') {
      // This line does not begin with #, so increment the count
      count++;
    }
  }
  return count;
}