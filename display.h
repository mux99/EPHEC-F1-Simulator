int* sort(float* data)
{
    int i;

    //evaluate data length
    int len = 0;
    for (i=0; data[i] != end; i++) len++;

    //making a sacrificial copy of data
    float data_cp[len];
    for (i=0; data[i] != end; i++)
    {
        data_cp[i] = data[i];
    }

    //finding the lowests for every spot on the leaderboard
    int* out = calloc(len+1,sizeof(int));
    out[len] = end;
    for (i=0;i<len;i++)
    {
        int j;
        int min = -1;
        for (j=0;j<len;j++)
        {
            if (data_cp[j] == -1) continue;
            if (data_cp[j] < data_cp[min] || min == -1)
            {
                min = j;
            }
        }
        out[i] = min;
        data_cp[min] = -1;
    }
    return out;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////s

void scoreboard_practice(int len_cars, struct Car* cars, float* data, struct GrandPrix gp,int now,int start)
{
    int* order = sort(data);
    int* order_s1 = sort(data+(11*(len_cars+1)));
    int* order_s2 = sort(data+(12*(len_cars+1)));
    int* order_s3 = sort(data+(13*(len_cars+1)));
    int i;
    printf("╔═══════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ PRACTICE %02d:%02d %63s Grand Prix ║\n",
                (now-start)/60,
                now-start-((int)((now-start)/60)*60),
                gp.location);
    printf("╠══╦════════════════╦═══╦═════════════╦════════╦════════╦════╦════════╦════════╦════════╦═╦═╣\n");
    printf("║%2s│%16s│%3s│%13s│%8s│%8s│%4s│%8s│%8s│%8s│%s│%s║\n","/","driver","num","team","best lap","diff","laps","best S1","best S2","best S3","P","O");
    printf("╠══╬════════════════╬═══╬═════════════╬════════╬════════╬════╬════════╬════════╬════════╬═╬═╣\n");
    for (i=0;i<len_cars;i++)
    {

        printf("║%2d│%16s│%3d│%13s│%8.3f│%8.3f│%4d│%8.3f│%8.3f│%8.3f│%s│%s║\n",
            i+1,
            cars[order[i]].driver,
            cars[order[i]].number,
            cars[order[i]].team,
            data[order[i]],
            i > 0 ? data[order[i]]-data[order[i-1]] : 0,
            (int)data[len_cars+1+order[i]],
            data[11*(len_cars+1)+order[i]],
            data[12*(len_cars+1)+order[i]],
            data[13*(len_cars+1)+order[i]],
            cars[order[i]].is_pit == true ? "P" : " ",
            cars[order[i]].is_out == true ? "O" : " ");
    }
    printf("╚══╩════════════════╩═══╩═════════════╩════════╩════════╩════╬════════╬════════╬════════╬═╩═╝\n");
    printf("                                                      num/pos║%-4d%4d│%-4d%4d│%-4d%4d║\n",
        cars[order_s1[0]].number,order_s1[0],
        cars[order_s2[0]].number,order_s2[0],
        cars[order_s3[0]].number,order_s3[0]);
    printf("                                          best sector overall║%8.3f│%8.3f│%8.3f║\n",
        data[11*(len_cars+1)+order_s1[0]],
        data[12*(len_cars+1)+order_s2[0]],
        data[13*(len_cars+1)+order_s3[0]]);
    printf("                                                             ╚════════╩════════╩════════╝\n");

    free(order);
    free(order_s1);
    free(order_s2);
    free(order_s3);
}


void scoreboard_qualif_1(int len_cars, struct Car* cars, float* data, struct GrandPrix gp,int now,int start)
{
    int* order = sort(data+(2*(len_cars+1)));
    int* order_s1 = sort(data+(11*(len_cars+1)));
    int* order_s2 = sort(data+(12*(len_cars+1)));
    int* order_s3 = sort(data+(13*(len_cars+1)));
    int i;
    printf("╔═══════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ QUALIFICATIONS ROUND 1 %02d:%02d %49s Grand Prix ║\n",
                (now-start)/60,
                now-start-((int)((now-start)/60)*60),
                gp.location);
    printf("╠══╦════════════════╦═══╦═════════════╦════════╦════════╦════╦════════╦════════╦════════╦═╦═╣\n");
    printf("║%2s│%16s│%3s│%13s│%8s│%8s│%4s│%8s│%8s│%8s│%s│%s║\n","/","driver","num","team","Q1","diff","laps","best S1","best S2","best S3","P","O");
    printf("╠══╬════════════════╬═══╬═════════════╬════════╬════════╬════╬════════╬════════╬════════╬═╬═╣\n");
    for (i=0;i<len_cars;i++)
    {

        printf("║%2d│%16s│%3d│%13s│%8.3f│%8.3f│%4d│%8.3f│%8.3f│%8.3f│%s│%s║\n",
            i+1,
            cars[order[i]].driver,
            cars[order[i]].number,
            cars[order[i]].team,
            data[order[i]+(2*(len_cars+1))],
            i > 0 ? data[order[i]+(2*(len_cars+1))]-data[order[i-1]+(2*(len_cars+1))] : 0,
            (int)data[(5*(len_cars+1))+order[i]],
            data[11*(len_cars+1)+order[i]],
            data[12*(len_cars+1)+order[i]],
            data[13*(len_cars+1)+order[i]],
            cars[order[i]].is_pit == true ? "P" : " ",
            cars[order[i]].is_out == true ? "O" : " ");
    }
    printf("╚══╩════════════════╩═══╩═════════════╩════════╩════════╩════╬════════╬════════╬════════╬═╩═╝\n");
    printf("                                                      num/pos║%-4d%4d│%-4d%4d│%-4d%4d║\n",
        cars[order_s1[0]].number,order_s1[0],
        cars[order_s2[0]].number,order_s2[0],
        cars[order_s3[0]].number,order_s3[0]);
    printf("                                          best sector overall║%8.3f│%8.3f│%8.3f║\n",
        data[11*(len_cars+1)+order_s1[0]],
        data[12*(len_cars+1)+order_s2[0]],
        data[13*(len_cars+1)+order_s3[0]]);
    printf("                                                             ╚════════╩════════╩════════╝\n");

    free(order);
    free(order_s1);
    free(order_s2);
    free(order_s3);
}



void scoreboard_qualif_2(int len_cars, struct Car* cars, float* data, struct GrandPrix gp,int now,int start)
{
    int* order = sort(data+(3*(len_cars+1)));
    int* order_s1 = sort(data+(11*(len_cars+1)));
    int* order_s2 = sort(data+(12*(len_cars+1)));
    int* order_s3 = sort(data+(13*(len_cars+1)));
    int i;
    printf("╔═══════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ QUALIFICATIONS ROUND 2 %02d:%02d %62s Grand Prix  ║\n",
                (now-start)/60,
                now-start-((int)((now-start)/60)*60),
                gp.location);
    printf("╠══╦════════════════╦═══╦═════════════╦════════╦════════╦════╦════════╦════════╦════════╦═╦═╣\n");
    printf("║%2s│%16s│%3s│%13s│%8s│%8s│%4s│%8s│%8s│%8s│%s│%s║\n","/","driver","num","team","Q1","diff","laps","best S1","best S2","best S3","P","O");
    printf("╠══╬════════════════╬═══╬═════════════╬════════╬════════╬════╬════════╬════════╬════════╬═╬═╣\n");
    for (i=0;i<len_cars;i++)
    {

        printf("║%2d│%16s│%3d│%13s│%8.3f│%8.3f│%4d│%8.3f│%8.3f│%8.3f│%s│%s║\n",
            i+1,
            cars[order[i]].driver,
            cars[order[i]].number,
            cars[order[i]].team,
            data[order[i]+(2*(len_cars+1))],
            i > 0 ? data[order[i]+(3*(len_cars+1))]-data[order[i-1]+(3*(len_cars+1))] : 0,
            (int)data[len_cars+1+order[i]],
            data[11*(len_cars+1)+order[i]],
            data[12*(len_cars+1)+order[i]],
            data[13*(len_cars+1)+order[i]],
            cars[order[i]].is_pit == true ? "P" : " ",
            cars[order[i]].is_out == true ? "O" : " ");
    }
    printf("╚══╩════════════════╩═══╩═════════════╩════════╩════════╩════╬════════╬════════╬════════╬═╩═╝\n");
    printf("                                                      num/pos║%-4d%4d│%-4d%4d│%-4d%4d║\n",
        cars[order_s1[0]].number,order_s1[0],
        cars[order_s2[0]].number,order_s2[0],
        cars[order_s3[0]].number,order_s3[0]);
    printf("                                          best sector overall║%8.3f│%8.3f│%8.3f║\n",
        data[11*(len_cars+1)+order_s1[0]],
        data[12*(len_cars+1)+order_s2[0]],
        data[13*(len_cars+1)+order_s3[0]]);
    printf("                                                             ╚════════╩════════╩════════╝\n");

    free(order);
    free(order_s1);
    free(order_s2);
    free(order_s3);
}



void scoreboard_qualif_3(int len_cars, struct Car* cars, float* data, struct GrandPrix gp,int now,int start)
{
    int* order = sort(data+len_cars+1);
    int* order_s1 = sort(data+(11*(len_cars+1)));
    int* order_s2 = sort(data+(12*(len_cars+1)));
    int* order_s3 = sort(data+(13*(len_cars+1)));
    int i;
    printf("╔═══════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ QUALIFICATIONS ROUND 3 %02d:%02d %62s Grand Prix  ║\n",
                (now-start)/60,
                now-start-((int)((now-start)/60)*60),
                gp.location);
    printf("╠══╦════════════════╦═══╦═════════════╦════════╦════════╦════╦════════╦════════╦════════╦═╦═╣\n");
    printf("║%2s│%16s│%3s│%13s│%8s│%8s│%4s│%8s│%8s│%8s│%s│%s║\n","/","driver","num","team","Q1","diff","laps","best S1","best S2","best S3","P","O");
    printf("╠══╬════════════════╬═══╬═════════════╬════════╬════════╬════╬════════╬════════╬════════╬═╬═╣\n");
    for (i=0;i<len_cars;i++)
    {

        printf("║%2d│%16s│%3d│%13s│%8.3f│%8.3f│%4d│%8.3f│%8.3f│%8.3f│%s│%s║\n",
            i+1,
            cars[order[i]].driver,
            cars[order[i]].number,
            cars[order[i]].team,
            data[order[i]+len_cars+1],
            i > 0 ? data[order[i]+len_cars+1]-data[order[i-1]+len_cars+1] : 0,
            (int)data[len_cars+1+order[i]],
            data[11*(len_cars+1)+order[i]],
            data[12*(len_cars+1)+order[i]],
            data[13*(len_cars+1)+order[i]],
            cars[order[i]].is_pit == true ? "P" : " ",
            cars[order[i]].is_out == true ? "O" : " ");
    }
    printf("╚══╩════════════════╩═══╩═════════════╩════════╩════════╩════╬════════╬════════╬════════╬═╩═╝\n");
    printf("                                                      num/pos║%-4d%4d│%-4d%4d│%-4d%4d║\n",
        cars[order_s1[0]].number,order_s1[0],
        cars[order_s2[0]].number,order_s2[0],
        cars[order_s3[0]].number,order_s3[0]);
    printf("                                          best sector overall║%8.3f│%8.3f│%8.3f║\n",
        data[11*(len_cars+1)+order_s1[0]],
        data[12*(len_cars+1)+order_s2[0]],
        data[13*(len_cars+1)+order_s3[0]]);
    printf("                                                             ╚════════╩════════╩════════╝\n");

    free(order);
    free(order_s1);
    free(order_s2);
    free(order_s3);
}





void scoreboard_sprint(int len_cars)
{
    printf("test4\n");
}

void scoreboard_race(int len_cars)
{
    printf("test5\n");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void display(int gp)
{
    int len_cars = countlines(cars_file);
    int len_gps = countlines(gps_file);

    int shmid_cars = shmget(shm_key, len_cars * sizeof(struct Car), 0666);
	struct Car *cars = shmat(shmid_cars, NULL, 0);

	int shmid_gps = shmget(shm_key + 1, len_gps * sizeof(struct Car), 0666);
	struct GrandPrix *gps = shmat(shmid_gps, NULL, 0);

	int shmid_data = shmget(shm_key + 2, (len_cars + 1) * 14 * sizeof(float), 0666);
	float *data = shmat(shmid_data, NULL, 0);

    int start = time(NULL);
    int now;
    while (0 == 0)
    {
        // practice
        switch (gps[gp].GP_state)
        {
            case 0: // idle state
                start = time(NULL);
                break;

            case 1: // practice
                system("clear");
                now = time(NULL);
                scoreboard_practice(len_cars,cars,data,gps[gp],now,start);
                break;

            case -1:
                system("clear");
                now = time(NULL);
                scoreboard_practice(len_cars,cars,data,gps[gp],now,start);
                printf("Practices are over\nsave scores to file? [Y/N]:\n");
                gps[gp].GP_state = 0;
                break;
            
            case 2: // qualifs round 1
                system("clear");
                now = time(NULL);
                scoreboard_qualif_1(len_cars,cars,data,gps[gp],now,start);
                break;

            case -2:
                system("clear");
                now = time(NULL);
                scoreboard_qualif_1(len_cars,cars,data,gps[gp],now,start);
                printf("Round 1 of Qualifications are over\nsave scores to file? [Y/N]:\n");
                gps[gp].GP_state = 0;
                break;
            
            case 3: // qualifs round 2
                system("clear");
                now = time(NULL);
                scoreboard_qualif_2(len_cars,cars,data,gps[gp],now,start);
                break;

            case -3:
                system("clear");
                now = time(NULL);
                scoreboard_qualif_2(len_cars,cars,data,gps[gp],now,start);
                printf("Round 1 of Qualifications are over\nsave scores to file? [Y/N]:\n");
                gps[gp].GP_state = 0;
                break;
            
            case 4: // qualifs round 3
                system("clear");
                now = time(NULL);
                scoreboard_qualif_3(len_cars,cars,data,gps[gp],now,start);
                break;

            case -4:
                system("clear");
                now = time(NULL);
                scoreboard_qualif_3(len_cars,cars,data,gps[gp],now,start);
                printf("Round 1 of Qualifications are over\nsave scores to file? [Y/N]:\n");
                gps[gp].GP_state = 0;
                break;

            case 5: // sprint
                system("clear");
                now = time(NULL);
                scoreboard_sprint(len_cars);
                break;

            case -5:
                break;

            case 6: // race
                system("clear");
                now = time(NULL);
                scoreboard_race(len_cars);
                break;

            case -6:
                break;

            default:
                exit(0);
        }
        sleep(1);
    }
}
