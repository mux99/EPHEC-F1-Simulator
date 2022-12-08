int* sort(float* data)
{
    
}

void get_scoreboard_practice(int len_cars, struct Car* cars, float* data, struct GrandPrix gp)
{
    int i;
    printf("+------------------------------------------------------------+\n");
    printf("|PRACTICE %40s Grand Prix|\n",gp.location);
    printf("+--+----------------+---+-------------+--------+--------+----+\n");
    printf("|%2s|%16s|%3s|%13s|%8s|%8s|%4s|\n","/","driver","num","team","best lap","diff","laps");
    printf("+--+----------------+---+-------------+--------+--------+----+\n");
    for (i=0;i<len_cars;i++)
    {

        printf("|%2d|%16s|%3d|%13s|%8.3f|%8.3f|%4d|\n",
            i,
            cars[i].driver,
            cars[i].number,
            cars[i].team,
            data[i],
            i > 0 ? data[i]-data[i-1] : 0,
            (int)data[len_cars+1+i]);
    }
    printf("+--+----------------+---+-------------+--------+--------+----+\n");
}

void get_scoreboard_qualifs(int len_cars)
{
    printf("test123\n");
}

void get_scoreboard_sprint(int len_cars)
{
    printf("test4\n");
}

void get_scoreboard_race(int len_cars)
{
    printf("test5\n");
}

void display(int gp)
{
    int len_cars = countlines(cars_file);
    int len_gps = countlines(gps_file);

    int shmid_cars = shmget(shm_key, len_cars * sizeof(struct Car), 0666);
	struct Car *cars = shmat(shmid_cars, NULL, 0);

	int shmid_gps = shmget(shm_key + 1, len_gps * sizeof(struct Car), 0666);
	struct GrandPrix *gps = shmat(shmid_gps, NULL, 0);

	int shmid_data = shmget(shm_key + 2, (len_cars + 1) * 14 * sizeof(int), 0666);
	float *data = shmat(shmid_data, NULL, 0);

    while (0 == 0)
    {
        system("clear");
        if (gps[gp].GP_state == 0)
        {
            get_scoreboard_practice(len_cars,cars,data,gps[gp]);
        }
        else if (gps[gp].GP_state == 1)
        {
            get_scoreboard_qualifs(len_cars);
        }
        else if (gps[gp].GP_state == 2)
        {
            get_scoreboard_qualifs(len_cars);
        }
        else if (gps[gp].GP_state == 3)
        {
            get_scoreboard_qualifs(len_cars);
        }
        else if (gps[gp].GP_state == 4)
        {
            get_scoreboard_sprint(len_cars);
        }
        else if (gps[gp].GP_state == 5)
        {
            get_scoreboard_race(len_cars);
        }
        else {
            exit(0);
        }
        sleep(1);
    }
}
