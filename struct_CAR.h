struct Car {
	bool is_null;
	int number;
	char* driver;
	char* team;

	int points;
}number, driver, team, points;


struct Car CAR_init(int number, char* driver, char* team, bool is_null) {
	struct Car out;
	out.number = allocSharedMem(sizeof(int));
	out.driver = allocSharedMem(sizeof(char)*array_len_1(driver));
	out.team = allocSharedMem(sizeof(char)*array_len_1(team));
	out.is_null = allocSharedMem(sizeof(bool));

	out.number = number;
	out.driver = driver;
	out.team = team;
	out.is_null = is_null;
	return out;
}