int get_time() {
	return rand() % ( + 1 - 25000) + 25000;
};

void car_sim_race(int i, int gp, struct Car* cars, int length, int step) {
    srand(time(NULL));
    int total_time = 0;
    int lap_count = 0;
    while (lap_count < length)
    {   
        int i;
        for (i=0; i < 3; i++) {
            //---TBD---
        }
    }
}

void car_sim_practice(int i, int gp, int length, int step) {
    int len_gps = countlines(gps_file);
    int len_cars = countlines(cars_file);
	int shmid_gps = shmget(shm_key,len_gps * sizeof(struct Car), 0666);
	struct GrandPrix* gps = shmat(shmid_gps,0,0);
    int shmid_data = shmget(shm_key,(len_cars+1) * 14 * sizeof(int), 0666);
	int* data = shmat(shmid_data,0,0);

    srand(time(NULL));
    int total_time = 0;
    int lap_time = 0;
    while (total_time < length) {
        int i;
        for (i=0; i < 3; i++) {
            int tmp = get_time();
            total_time += tmp;
            lap_time += tmp;
        }
        switch (step)
        {
        case 0:
            if (lap_time > data[gps[gp].practice+i]) {
                data[gps[gp].practice+i] = lap_time; 
            }
            break;
        case 1:
            data[gps[gp].qualif_1_laps+i]++;
            if (lap_time > data[gps[gp].qualif_1_best_lap+i]) {
                data[gps[gp].qualif_1_best_lap+i] = lap_time;
            }
            break;
        case 2:
            data[gps[gp].qualif_2_laps+i]++;
            if (lap_time > data[gps[gp].qualif_2_best_lap+i]) {
                data[gps[gp].qualif_2_best_lap+i] = lap_time;
            }
            break;
        case 3:
            data[gps[gp].qualif_3_laps+i]++;
            if (lap_time > data[gps[gp].qualif_3_best_lap+i]) {
                data[gps[gp].qualif_3_best_lap+i] = lap_time;
            }
            break;
        }
        lap_time = 0;
    }

    shmdt(gps);
    shmdt(data);
}