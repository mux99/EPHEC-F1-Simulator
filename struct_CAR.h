struct Car {
	bool is_null;
	//data
	int number;
	char* driver;
	char* team;

	//flags
	bool is_out;
	bool is_pit;

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
	return out;
}