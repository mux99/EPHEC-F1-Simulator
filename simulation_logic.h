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

void qualify(float* data, struct Car *cars, int len_cars, int step)
{
	int i;
	switch(step)
	{
		case 1:
			int* order_q1 = sort(data+(2*(len_cars+1)));
			for (i=len_cars-1;i>=15;i--)
			{
				cars[order_q1[i]].is_out_q2 = true;
				data[(6*(len_cars+1))+i] = order_q1[i];
			}
			free(order_q1);
			break;
		
		case 2:
			int* order_q2 = sort(data+(3*(len_cars+1)));
			for (i=14;i>=10;i--)
			{
				cars[order_q2[i]].is_out_q3 = true;
				data[(6*(len_cars+1))+i] = order_q2[i];
			}
			free(order_q2);
			break;

		case 3:
			int* order_q3 = sort(data+(4*(len_cars+1)));
			for (i=9;i>=0;i--)
			{
				data[(6*(len_cars+1))+i] = order_q3[i];
			}
			free(order_q3);
			break;
	}
}

void ask_save()
{
	char input; int c;
	scanf("%c",&input);
	while ((c = getchar()) != '\n' && c != EOF);
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

	// // P1
	// gps[gp].GP_state = 1;
	// practice(gp, len_cars);
	// gps[gp].GP_state = -1;
	// ask_save();

	// if (type == 1) {
	// 	// P2
	// 	gps[gp].GP_state = 1;
	// 	practice(gp, len_cars);
	// 	gps[gp].GP_state = -1;
	// 	ask_save();

	// 	// P3
	// 	gps[gp].GP_state = 1;
	// 	practice(gp, len_cars);
	// 	gps[gp].GP_state = -1;
	// 	ask_save();
	// }

	// Q1
	gps[gp].GP_state = 2;
	qualifications(gp, len_cars, 0, 1080);
	gps[gp].GP_state = -2;
	qualify(data,cars,len_cars,1);
	ask_save();

	// Q2
	gps[gp].GP_state = 3;
	qualifications(gp, len_cars, 1, 900);
	gps[gp].GP_state = -3;
	qualify(data,cars,len_cars,2);
	ask_save();

	// Q3
	gps[gp].GP_state = 4;
	qualifications(gp, len_cars, 2, 720);
	gps[gp].GP_state = -4;
	qualify(data,cars,len_cars,3);
	ask_save();

	// if (type == 2)
	// {
	// 	// P2
	// 	gps[gp].GP_state = 1;
	// 	practice(gp, len_cars);
	// 	gps[gp].GP_state = -1;
	// 	ask_save();

	// 	// SPRINT
	// 	gps[gp].GP_state = 5;
	// 	sprint(gp, len_cars, gps[gp].sprint_laps_number);
	// 	gps[gp].GP_state = -5;
	// 	ask_save();
	// }

	// // RACE
	// gps[gp].GP_state = 6;
	// race(gp, len_cars, gps[gp].race_laps_number);
	// gps[gp].GP_state = -6;
	// ask_save();

	// end gp
	gps[gp].GP_state = 100;
	shmdt(gps);
	int status;
	waitpid(pid,&status,0);
}