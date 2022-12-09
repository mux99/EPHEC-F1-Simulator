////SIMULATION/////////////////////////////////////////////////////////////////////////

void practice(int gp, int len_cars)
{
	int i; int status;
	pid_t pid_childs[len_cars];
	for (i = 0; i < len_cars; i++)
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			car_sim_practice(i, 3600, gp);
			exit(0);
		}
		else if (pid > 0) pid_childs[i] = pid;
	}
	for (i = 0; i < len_cars; i++) waitpid(pid_childs[i], &status, 0);
}

void qualifications(int gp, int len_cars, int step, int lenght)
{
	int i; int status;
	pid_t pid_childs[len_cars];
	for (i = 0; i < len_cars; i++)
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			car_sim_qualifs(i, gp, lenght, step);
			exit(0);
		}
		else if (pid > 0) pid_childs[i] = pid;
	}
	
	for (i = 0; i < len_cars; i++) waitpid(pid_childs[i], &status, 0);
}

void sprint(int gp, int len_cars, int lenght)
{
	int i; int status;
	pid_t pid_childs[len_cars];
	for (i = 0; i < len_cars; i++)
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			car_sim_sprint(i, gp, lenght);
			exit(0);
		}
		else if (pid > 0) pid_childs[i] = pid;
	}
	for (i = 0; i < len_cars; i++) waitpid(pid_childs[i], &status, 0);
}

void race(int gp, int len_cars, int lenght)
{
	int i; int status;
	pid_t pid_childs[len_cars];
	for (i = 0; i < len_cars; i++)
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			car_sim_race(i, gp, lenght);
			exit(0);
		}
		else if (pid > 0) pid_childs[i] = pid;
	}
	for (i = 0; i < len_cars; i++) waitpid(pid_childs[i], &status, 0);
}

////ORGANISATION/////////////////////////////////////////////////////////////////////////////////////////////////////////

void qualify()
{
}

void run_gp(int gp, int len_cars, struct GrandPrix *gps, float *data, struct Car *cars)
{
	int i;
	pid_t pid = fork();
	if (pid == 0)
	{
		display(gp);
		exit(0);
	}

	int type = gps[gp].weekend_type;

	// clear shared memory
	wipe_data(data,len_cars);

	char input;

	// P1
	gps[gp].GP_state = 1;
	practice(gp, len_cars);
	gps[gp].GP_state = -1;
	scanf("%c",&input);
	if (input == 'y') save_data(gps,cars,data,gp,1);

	if (type == 1) {
		// P2
		gps[gp].GP_state = 1;
		practice(gp, len_cars);
		gps[gp].GP_state = -1;
		scanf("%c",&input);
		if (input == 'y') save_data(gps,cars,data,gp,1);

		// P3
		gps[gp].GP_state = 1;
		practice(gp, len_cars);
		gps[gp].GP_state = -1;
		scanf("%c",&input);
		if (input == 'y') save_data(gps,cars,data,gp,1);
	}

	// Q1
	gps[gp].GP_state = 2;
	qualifications(gp, len_cars, 0, 1080);
	gps[gp].GP_state = -2;
	scanf("%c",&input);
	if (input == 'y') save_data(gps,cars,data,gp,2);

	// Q2
	gps[gp].GP_state = 3;
	qualifications(gp, len_cars, 1, 900);
	gps[gp].GP_state = -3;
	scanf("%c",&input);
	if (input == 'y') save_data(gps,cars,data,gp,3);

	// // Q3
	// wipe_data_segment(data+(11*(len_cars+1)));
	// wipe_data_segment(data+(12*(len_cars+1)));
	// wipe_data_segment(data+(13*(len_cars+1)));
	// wipe_data_segment(data+(5*(len_cars+1)));
	// gps[gp].GP_state = 4;
	// qualifications(gp, len_cars, 2, 720);
	// gps[gp].GP_state = -4;
	// scanf("%c",&input);
	// if (input == 'y') save_data(gps,cars,data,gp,1);

	// if (type == 2)
	// {
	// 	// P2
	// 	wipe_data_segment(data+(11*(len_cars+1)));
	// 	wipe_data_segment(data+(12*(len_cars+1)));
	// 	wipe_data_segment(data+(13*(len_cars+1)));
	// 	gps[gp].GP_state = 1;
	// 	practice(gp, len_cars);
	// 	gps[gp].GP_state = -1;
	// 	scanf("%c",&input);
	// 	if (input == 'y') save_data(gps,cars,data,gp,1);

	// 	// SPRINT
	// 	wipe_data_segment(data+(11*(len_cars+1)));
	// 	wipe_data_segment(data+(12*(len_cars+1)));
	// 	wipe_data_segment(data+(13*(len_cars+1)));
	// 	gps[gp].GP_state = 5;
	// 	sprint(gp, len_cars, gps[gp].sprint_laps_number);
	// 	gps[gp].GP_state = -5;
	// 	scanf("%c",&input);
	// 	if (input == 'y') save_data(gps,cars,data,gp,1);
	// }

	// // RACE
	// wipe_data_segment(data+(11*(len_cars+1)));
	// wipe_data_segment(data+(12*(len_cars+1)));
	// wipe_data_segment(data+(13*(len_cars+1)));
	// gps[gp].GP_state = 6;
	// race(gp, len_cars, gps[gp].race_laps_number);
	// gps[gp].GP_state = -6;
	// scanf("%c",&input);
	// if (input == 'y') save_data(gps,cars,data,gp,1);

	// end gp
	gps[gp].GP_state = 100;
	shmdt(gps);
	int status;
	waitpid(pid,&status,0);
}