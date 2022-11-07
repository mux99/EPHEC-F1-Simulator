struct Car {
	bool is_null;
	int number;
	char* driver;
	char* team;

	int points;
}number, driver, team, points;


struct Car CAR_init(int number, char* driver, char* team, bool is_null) {
	struct Car out;
	out.number = number;
	out.driver = driver;
	out.team = team;
	out.is_null = is_null;
	return out;
}