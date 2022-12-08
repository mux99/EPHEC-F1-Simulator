/* return lenght of given NULL terminated array */
int array_len_1(char *list)
{
	int len;
	for (len = 0; list[len] != '\0'; len++)
	{
	}
	return len;
}

void qualify()
{
}

struct GrandPrix *init_GPs(struct GrandPrix* cars, char *data, int car_lenght)
{
	char **lines = split(data, "\r");
	char **words;
	int i;
	for (i = 0; lines[i] != NULL; i++)
	{
		words = split(lines[i], ",");
		cars[i] = GP_init(i, words[0], atoi(words[1]), atoi(words[2]), car_lenght, false);
	}
	cars[i] = GP_init(i, "NULL", 50, 1, 0, true);
	free(lines);
	free(words);
}

struct Car *init_CARs(struct Car* cars, char *data)
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

////SIMULATION/////////////////////////////////////////////////////////////////////////

void practice(int gp, int len_cars)
{
	int i;
	pid_t pid_childs[len_cars];
	for (i = 0; i < len_cars; i++)
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			car_sim_practice(i, 3600000, gp);
			exit(0);
		}
		else if (pid > 0)
		{
			pid_childs[i] = pid;
		}
		else
		{
			perror("fork() failed");
			exit(1);
		}
	}
	int status;
	for (i = 0; i < len_cars; i++)
	{
		waitpid(pid_childs[i], &status, 0);
	}
}

void qualifications(int gp, int len_cars, int step, int lenght)
{
	int i;
	pid_t pid_childs[len_cars];
	for (i = 0; i < len_cars; i++)
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			car_sim_qualifs(i, gp, lenght, step);
			exit(0);
		}
		else if (pid > 0)
		{
			pid_childs[i] = pid;
		}
		else
		{
			perror("fork() failed");
			exit(1);
		}
	}
	int status;
	for (i = 0; i < len_cars; i++)
	{
		waitpid(pid_childs[i], &status, 0);
	}
}

void sprint(int gp, int len_cars, int lenght)
{
	int i;
	pid_t pid_childs[len_cars];
	for (i = 0; i < len_cars; i++)
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			car_sim_sprint(i, gp, lenght);
			exit(0);
		}
		else if (pid > 0)
		{
			pid_childs[i] = pid;
		}
		else
		{
			perror("fork() failed");
			exit(1);
		}
	}
	int status;
	for (i = 0; i < len_cars; i++)
	{
		waitpid(pid_childs[i], &status, 0);
	}
}

void race(int gp, int len_cars, int lenght)
{
	int i;
	pid_t pid_childs[len_cars];
	for (i = 0; i < len_cars; i++)
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			car_sim_race(i, gp, lenght);
			exit(0);
		}
		else if (pid > 0)
		{
			pid_childs[i] = pid;
		}
		else
		{
			perror("fork() failed");
			exit(1);
		}
	}
	int status;
	for (i = 0; i < len_cars; i++)
	{
		waitpid(pid_childs[i], &status, 0);
	}
}

void weekend1(int gp, int len_cars, int len_gps, float *data, struct Car *cars)
{
	int shmid_gps = shmget(shm_key + 1, len_gps * sizeof(struct Car), 0666);
	struct GrandPrix *gps = shmat(shmid_gps, NULL, 0);

	int i;
	pid_t pid = fork();
	if (pid == 0)
	{
		display(gp);
		exit(0);
	}

	// clear shared memory
	int len_data = (len_cars + 1) * 14;
	for (i = 0; i < len_data; i++)
	{
		if (((i + 1) % (len_cars + 1) == 0) && (i > 0))
		{
			data[i] = end;
		}
		else
		{
			data[i] = 0;
		}
	}

	practice(gp, len_cars);
	//gps[gp].GP_state = 1;

	// qualifications(gp, len_cars, 0, 1080000);
	// gps[gp].GP_state = 2;

	// qualifications(gp, len_cars, 1, 900000);
	// gps[gp].GP_state = 3;

	// qualifications(gp, len_cars, 2, 720000);
	// gps[gp].GP_state = 5;

	// race(gp, len_cars, gps[gp].race_laps_number);

	// end gp
	gps[gp].GP_state = 100;
	shmdt(gps);
}

void weekend2(int gp, int len_cars, int len_gps, float *data, struct Car *cars)
{
	int shmid_gps = shmget(shm_key + 1, len_gps * sizeof(struct Car), 0666);
	struct GrandPrix *gps = shmat(shmid_gps, NULL, 0);

	int i;
	pid_t pid = fork();
	if (pid == 0)
	{
		display(gp);
		exit(0);
	}

	int len_data = (len_cars + 1) * 14;
	for (i = 0; i < len_data; i++)
	{
		if (((i + 1) % (len_cars + 1) == 0) && (i > 0))
		{
			data[i] = end;
		}
		else
		{
			data[i] = 0;
		}
	}
	practice(gp, len_cars);
	gps[gp].GP_state = 1;

	qualifications(gp, len_cars, 0, 1080000);
	gps[gp].GP_state = 2;

	qualifications(gp, len_cars, 1, 900000);
	gps[gp].GP_state = 3;

	qualifications(gp, len_cars, 2, 720000);
	gps[gp].GP_state = 4;

	sprint(gp, len_cars, gps[gp].sprint_laps_number);
	gps[gp].GP_state = 5;

	race(gp, len_cars, gps[gp].race_laps_number);

	// end gp
	gps[gp].GP_state = 100;
	shmdt(gps);
}