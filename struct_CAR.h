struct Car {
	int number;
	char* driver;
	char* team;

	int points = 0; //(total)
};

Car CAR__init(int number, char* driver, char* team) {
	Car out;
	out = { .number = number, .driver = driver, .team = team}
}