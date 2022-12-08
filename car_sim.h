float get_time()
{
	return ((float)rand()/(float)(RAND_MAX/21.0))+25.0;
}

void car_sim_practice(int i, int length, int gp)
{
	srand(time(NULL)+getpid());
	int len_cars = countlines(cars_file);
	int shmid_data = shmget(shm_key + 2, (len_cars + 1) * 14 * sizeof(float), 0666);
	float *data = shmat(shmid_data, 0, 0);

	int total_time = 0;
	while (total_time < length)
	{
		int lap_time = 0;
		int j;
		for (j = 0; j < 3; j++)
		{
			float tmp = get_time();
			unsigned int time_to_sleep = tmp*speed;
			while(time_to_sleep) time_to_sleep = sleep(time_to_sleep);
			total_time += tmp;
			lap_time += tmp;
			if (data[((j+11)*(len_cars+1))+i] > tmp || data[i] == 0) {
				data[((j+11)*(len_cars+1))+i] = tmp;
			}
		}
		data[len_cars+1+i]++;
		if (lap_time < data[i] || data[i] == 0)
		{
			data[i] = lap_time;

		}
	}
	shmdt(data);
}

void car_sim_qualifs(int i, int gp, int length, int step)
{
	srand(time(NULL)+getpid());
	int len_cars = countlines(cars_file);
	int shmid_data = shmget(shm_key + 2, (len_cars + 1) * 14 * sizeof(float), 0666);
	float *data = shmat(shmid_data, 0, 0);

	int shmid_cars = shmget(shm_key, len_cars * sizeof(struct Car), IPC_CREAT | 0666);
	struct Car *cars = shmat(shmid_cars, NULL, 0);

	if (cars[i].is_out_qualifs == true){
		return;
	}

	int total_time = 0;
	while (total_time < length)
	{
		int lap_time = 0;
		int j;
		for (j = 0; j < 3; j++)
		{
			float tmp = get_time();
			unsigned int time_to_sleep = tmp*speed;
			while(time_to_sleep) time_to_sleep = sleep(time_to_sleep);
			total_time += tmp;
			lap_time += tmp;
			if (data[((j+11)*(len_cars+1))+i] > tmp || data[i] == 0) {
				data[((j+11)*(len_cars+1))+i] = tmp;
			}
		}
		if ((step == 0) && ((lap_time < data[len_cars+1+i]) || data[i] == 0))
		{
			data[len_cars+1+i] = lap_time;
		}
		else if ((step == 1) && ((lap_time < data[((len_cars+1)*2)+i]) || data[i] == 0))
		{
			data[((len_cars+1)*2)+i] = lap_time;
		}
		else if ((step == 2) && ((lap_time < data[((len_cars+1)*3)+i]) || data[i] == 0))
		{
			data[((len_cars+1)*3)+i] = lap_time;
		}
	}
}

void car_sim_sprint(int i, int gp, int length)
{
	srand(time(NULL)+getpid());
	int len_cars = countlines(cars_file);
	int shmid_data = shmget(shm_key + 2, (len_cars + 1) * 14 * sizeof(float), 0666);
	float *data = shmat(shmid_data, 0, 0);

	int total_time = 0;
	int lap_count;
	for (lap_count=0;lap_count < length;lap_count++)
	{
		int j;
		int lap_time = 0;
		for (j=0; j < 3; j++)
		{
			float tmp = get_time();
			unsigned int time_to_sleep = tmp*speed;
			while(time_to_sleep) time_to_sleep = sleep(time_to_sleep);
			total_time += tmp;
			lap_time += tmp;
			if (data[((j+11)*(len_cars+1))+i] > tmp || data[i] == 0) {
				data[((j+11)*(len_cars+1))+i] = tmp;
			}
		}
		if (lap_time < data[(4*(len_cars+1))+i] || data[i] == 0)
		{
			data[(4*(len_cars+1))+i] = lap_time;
		}
	}
}

void car_sim_race(int i, int gp, int length)
{
	srand(time(NULL)+getpid());
	int len_cars = countlines(cars_file);
	int shmid_data = shmget(shm_key + 2, (len_cars + 1) * 14 * sizeof(float), 0666);
	float *data = shmat(shmid_data, 0, 0);

	int total_time = 0;
	int lap_count;
	for (lap_count=0;lap_count < length;lap_count++)
	{
		int j;
		int lap_time = 0;
		for (j=0; j < 3; j++)
		{
			float tmp = get_time();
			unsigned int time_to_sleep = tmp*speed;
			while(time_to_sleep) time_to_sleep = sleep(time_to_sleep);
			total_time += tmp;
			lap_time += tmp;
			if (data[((j+11)*(len_cars+1))+i] > tmp || data[i] == 0) {
				data[((j+11)*(len_cars+1))+i] = tmp;
			}
		}
		if (lap_time < data[(5*(len_cars+1))+i] || data[i] == 0)
		{
			data[(5*(len_cars+1))+i] = lap_time;
			data[(6*(len_cars+1))+i] = total_time;
		}
	}
}