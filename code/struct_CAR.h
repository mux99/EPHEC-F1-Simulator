struct Car {
	bool is_null;
	//data
	int number;
	char* driver;
	char* team;

	//flags
	bool is_out;
	bool is_pit;
	bool is_out_q2;
	bool is_out_q3;

	//scores
	int points;

};


struct Car CAR_init(int number, char* driver, char* team, bool is_out) {
	struct Car out;
	out.number = number;
	out.driver = driver;
	out.team = team;
	out.is_out = is_out;
	out.is_pit = false;
	out.is_out_q2 = false;
	out.is_out_q3 = false;
	out.points = 0;
	return out;
}

void init_CARs(struct Car* cars, char *data)
{
	char **lines = split(data, "\n");
	char **words;
	int i;
	for (i = 0; lines[i] != NULL; i++)
	{
		if (lines[i][0] == '#') continue;
		words = split(lines[i], ",");
		cars[i] = CAR_init(atoi(words[0]), words[1], words[2], atoi(words[3]) == 0 ? false : true);
	}
	free(lines);
	free(words);
}