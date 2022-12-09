struct Car {
	bool is_null;
	//data
	int number;
	char* driver;
	char* team;

	//flags
	bool is_out;
	bool is_pit;
	bool is_out_qualifs;

	//scores
	int points;

};


struct Car CAR_init(int number, char* driver, char* team, bool is_null) {
	struct Car out;
	out.number = number;
	out.driver = driver;
	out.team = team;
	out.is_null = is_null;
	out.is_out = false;
	out.is_pit = false;
	out.is_out_qualifs = false;
	return out;
}

void init_CARs(struct Car* cars, char *data)
{
	char **lines = split(data, "\n");
	char **words;
	int i;
	for (i = 0; lines[i] != NULL; i++)
	{
		words = split(lines[i], ",");
		cars[i] = CAR_init(atoi(words[0]), words[1], words[2], false);
	}
	cars[i] = CAR_init(0, "NULL", "NULL", true);
	free(lines);
	free(words);
}