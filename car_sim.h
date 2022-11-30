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

void car_sim_practice(int i, struct GrandPrix gp, struct Car* cars, int length, int step) {
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
            if (lap_time > gp.practice[i]) {
                gp.practice[i] = lap_time; 
            }
            break;
        case 1:
            gp.qualifications_1_laps[i]++;
            if (lap_time > gp.qualifications_1_best_lap[i]) {
                gp.qualifications_1_best_lap[i] = lap_time;
            }
            break;
        case 2:
            gp.qualifications_2_laps[i]++;
            if (lap_time > gp.qualifications_2_best_lap[i]) {
                gp.qualifications_2_best_lap[i] = lap_time;
            }
            break;
        case 3:
            gp.qualifications_3_laps[i]++;
            if (lap_time > gp.qualifications_3_best_lap[i]) {
                gp.qualifications_3_best_lap[i] = lap_time;
            }
            break;
        }
        lap_time = 0;
    }
}