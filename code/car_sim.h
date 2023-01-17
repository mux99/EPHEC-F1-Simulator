//generate time for a signle sector
float get_time()
{
	return 25.0 + (rand() / (float) RAND_MAX * 45.0 - 25.0);
}

//generate thr number of turns before a pit
int get_pit()
{
	return pit_min + (rand() / (float) RAND_MAX * pit_max - pit_min);
}

void car_sim_practice(int i, int length, int gp)
{
	//inititalize randomness
	srand(time(NULL)+getpid());

	//attach shared memory
	int len_cars = countlines(cars_file);
	int shmid_cars = shmget(shm_key, len_cars * sizeof(struct Car), IPC_CREAT | 0666);
	struct Car *cars = shmat(shmid_cars, NULL, 0);
	int shmid_data = shmget(shm_key + 2, (len_cars + 1) * 14 * sizeof(float), 0666);
	float *data = shmat(shmid_data, 0, 0);

	unsigned int time_to_sleep;
	int pits = get_pit();
	if (cars[i].is_out == true){
		return;
	}

	//loop for each turn
	int total_time = 0;
	while (total_time < length)
	{
		//loop for each sector
		float lap_time = 0;
		int j;
		for (j = 0; j < 3; j++)
		{
			//pit trigger
			if (j == 2 && pits <= 0)
			{
				sem_wait(&sem_cars);
				cars[i].is_pit = true;
				sem_post(&sem_cars);
				time_to_sleep = pit_time/speed;
				while(time_to_sleep) time_to_sleep = sleep(time_to_sleep);
				sem_wait(&sem_cars);
				cars[i].is_pit = false;
				sem_post(&sem_cars);
				pits = get_pit();
			}

			float tmp = get_time();
			if (total_time+tmp > length) return;
			
			//sleep time of turn
			time_to_sleep = tmp/speed;
			while(time_to_sleep) time_to_sleep = sleep(time_to_sleep);
			total_time += tmp;
			lap_time += tmp;

			//update data (sectors)
			if (data[((j+s1)*(len_cars+1))+i] > tmp || data[((j+s1)*(len_cars+1))+i] == 0) {
				sem_wait(&sem_data);
				data[((j+s1)*(len_cars+1))+i] = tmp;
				sem_post(&sem_data);
			}
		}
		//update data
		sem_wait(&sem_data);
		data[lpc*(len_cars+1)+i]++;
		if (lap_time < data[i] || data[i] == 0)
		{
			data[i] = lap_time;

		}
		sem_post(&sem_data);
		pits--;
	}
	shmdt(cars);
	shmdt(data);
}

void car_sim_qualifs(int i, int gp, int length, int step)
{
	//inititalize randomness
	srand(time(NULL)+getpid());

	//attach shared memory
	int len_cars = countlines(cars_file);
	int shmid_data = shmget(shm_key + 2, (len_cars + 1) * 14 * sizeof(float), 0666);
	float *data = shmat(shmid_data, 0, 0);
	int shmid_cars = shmget(shm_key, len_cars * sizeof(struct Car), IPC_CREAT | 0666);
	struct Car *cars = shmat(shmid_cars, NULL, 0);

	int pits = get_pit();
	unsigned int time_to_sleep;
	if (cars[i].is_out_q3 == true || cars[i].is_out_q2 == true || cars[i].is_out == true){
		return;
	}

	//loop for each turn
	float total_time = 0;
	while (total_time < length)
	{
		//loop for each sector
		float lap_time = 0;
		int j;
		for (j = 0; j < 3; j++)
		{
			//pit trigger
			if (j == 2 && pits <= 0)
			{
				sem_wait(&sem_cars);
				cars[i].is_pit = true;
				sem_post(&sem_cars);
				time_to_sleep = pit_time/speed;
				while(time_to_sleep) time_to_sleep = sleep(time_to_sleep);
				sem_wait(&sem_cars);
				cars[i].is_pit = false;
				sem_post(&sem_cars);
				pits = get_pit();
			}
			float tmp = get_time();
			if (total_time+tmp > length) return;

			//sleep time of turn
			time_to_sleep = tmp/speed;
			while(time_to_sleep) time_to_sleep = sleep(time_to_sleep);
			total_time += tmp;
			lap_time += tmp;

			if (data[((j+s1)*(len_cars+1))+i] > tmp || data[((j+s1)*(len_cars+1))+i] == 0) {
				sem_wait(&sem_data);
				data[((j+s1)*(len_cars+1))+i] = tmp;
				sem_post(&sem_data);
			}
		}
		sem_wait(&sem_data);
		data[lpc*(len_cars+1)+i]++;
		if ((step == 0) && ((lap_time < data[(q1*(len_cars+1))+i]) || data[(q1*(len_cars+1))+i] == 0))
		{
			data[(q1*(len_cars+1))+i] = lap_time;
		}
		else if ((step == 1) && ((lap_time < data[(q2*(len_cars+1))+i]) || data[(q2*(len_cars+1))+i] == 0))
		{
			data[(q2*(len_cars+1))+i] = lap_time;
		}
		else if ((step == 2) && ((lap_time < data[(q3*(len_cars+1))+i]) || data[(q3*(len_cars+1))+i] == 0))
		{
			data[(q3*(len_cars+1))+i] = lap_time;
		}
		sem_post(&sem_data);
		pits--;
	}
	shmdt(cars);
	shmdt(data);
}

void car_sim_sprint(int i, int gp, int length)
{
	//inititalize randomness
	srand(time(NULL)+getpid());

	//attach shared memory
	int len_cars = countlines(cars_file);
	int shmid_cars = shmget(shm_key, len_cars * sizeof(struct Car), IPC_CREAT | 0666);
	struct Car *cars = shmat(shmid_cars, NULL, 0);
	int shmid_data = shmget(shm_key + 2, (len_cars + 1) * 14 * sizeof(float), 0666);
	float *data = shmat(shmid_data, 0, 0);
	unsigned int time_to_sleep;
	int pits = get_pit();

	sem_wait(&sem_cars);
	if (cars[i].is_out == true){
		return;
	}
	sem_post(&sem_cars);

	//loop for each turn
	float total_time = 0;
	int lap_count;
	for (lap_count=0;lap_count < length;lap_count++)
	{
		//loop for each sector
		int j;
		float lap_time = 0;
		for (j=0; j < 3; j++)
		{
			//pit trigger
			if (j == 2 && pits <= 0)
			{
				sem_wait(&sem_cars);
				cars[i].is_pit = true;
				sem_post(&sem_cars);
				time_to_sleep = pit_time/speed;
				while(time_to_sleep) time_to_sleep = sleep(time_to_sleep);
				sem_wait(&sem_cars);
				cars[i].is_pit = false;
				sem_post(&sem_cars);
				pits = get_pit();
			}
			float tmp = get_time();

			//sleep time of turn
			time_to_sleep = tmp/speed;
			while(time_to_sleep) time_to_sleep = sleep(time_to_sleep);
			total_time += tmp;
			lap_time += tmp;
			
			if (data[((j+s1)*(len_cars+1))+i] > tmp || data[((j+s1)*(len_cars+1))+i] == 0) {
				sem_wait(&sem_data);
				data[((j+s1)*(len_cars+1))+i] = tmp;
				sem_post(&sem_data);
			}
		}
		sem_wait(&sem_data);
		data[lpc*(len_cars+1)+i]++;
		data[(sti*(len_cars+1))+i] = total_time;
		if (lap_time < data[(slp*(len_cars+1))+i] || data[(slp*(len_cars+1))+i] == 0)
		{
			data[(slp*(len_cars+1))+i] = lap_time;
		}
		sem_post(&sem_data);
		pits--;
	}
	shmdt(cars);
	shmdt(data);
}

void car_sim_race(int i, int gp, int length)
{
	//inititalize randomness
	srand(time(NULL)+getpid());

	//attach shared memory
	int len_cars = countlines(cars_file);
	int shmid_cars = shmget(shm_key, len_cars * sizeof(struct Car), IPC_CREAT | 0666);
	struct Car *cars = shmat(shmid_cars, NULL, 0);
	int shmid_data = shmget(shm_key + 2, (len_cars + 1) * 14 * sizeof(float), 0666);
	float *data = shmat(shmid_data, 0, 0);

	int pits = get_pit();
	bool as_pit = false;
	unsigned int time_to_sleep;

	sem_wait(&sem_cars);
	if (cars[i].is_out == true){
		return;
	}
	sem_post(&sem_cars);

	//loop for each turn
	float total_time = 0;
	int lap_count;
	for (lap_count=0;lap_count < length;lap_count++)
	{
		//loop for each sector
		int j;
		float lap_time = 0;
		if (lap_count == length/2 && as_pit == false){
			pits = 0;
		}
		for (j=0; j < 3; j++)
		{
			//pit trigger
			if (j == 2 && pits <= 0)
			{
				as_pit = true;
				sem_wait(&sem_cars);
				cars[i].is_pit = true;
				sem_post(&sem_cars);
				time_to_sleep = pit_time/speed;
				while(time_to_sleep) time_to_sleep = sleep(time_to_sleep);
				sem_wait(&sem_cars);
				cars[i].is_pit = false;
				sem_post(&sem_cars);
				pits = get_pit();
			}
			float tmp = get_time();
			time_to_sleep = tmp/speed;
			while(time_to_sleep) time_to_sleep = sleep(time_to_sleep);
			total_time += tmp;
			lap_time += tmp;
			if (data[((j+s1)*(len_cars+1))+i] > tmp || data[((j+s1)*(len_cars+1))+i] == 0) {
				sem_wait(&sem_data);
				data[((j+s1)*(len_cars+1))+i] = tmp;
				sem_post(&sem_data);
			}
		}
		sem_wait(&sem_data);
		data[lpc*(len_cars+1)+i]++;
		data[rti*(len_cars+1)+i] = total_time;
		if (lap_time < data[rlp*(len_cars+1)+i] || data[rlp*(len_cars+1)+i] == 0)
		{
			data[(rlp*(len_cars+1))+i] = lap_time;
		}
		sem_post(&sem_data);
		pits--;
	}
	shmdt(cars);
	shmdt(data);
}