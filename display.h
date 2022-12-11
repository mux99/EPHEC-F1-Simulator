int* sort(float* data)
{
    int i;

    //evaluate data length
    int len = 0;
    for (i=0; data[i] != end; i++) len++;

    // instantiate output
    int* out = calloc(len+1,sizeof(int));
    out[len] = end;

    //making a sacrificial copy of data
    float data_cp[len];
    int non_zeros = 0;
    for (i=0; data[i] != end; i++)
    {
        if (data[i] != 0) non_zeros++;
        data_cp[i] = data[i];
        out[i] = i;
    }
    if (non_zeros == 0) return out;

    //finding the lowests for every spot on the leaderboard
    for (i=0;i<len;i++)
    {
        int j;
        int min = -1;
        int last_zero = 0;
        for (j=0;j<len;j++)
        {
            if (data_cp[j] == -1) continue;
            if (data_cp[j] == 0) last_zero = j;
            if (data_cp[j] > 0 && (data_cp[j] < data_cp[min] || min == -1)) min = j;
        }
        if (min == -1) {
            out[i] = last_zero;
            data_cp[last_zero] = -1;
        } else {
            out[i] = min;
            data_cp[min] = -1;
        }
        
    }
    return out;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////s

void scoreboard_practice(int len_cars, struct Car* cars, float* data, struct GrandPrix gp,int now,int start)
{
    int* order = sort(p1*(len_cars+1)+data);
    int* order_s1 = sort(data+(s1*(len_cars+1)));
    int* order_s2 = sort(data+(s2*(len_cars+1)));
    int* order_s3 = sort(data+(s3*(len_cars+1)));
    int i;
    printf("╔═══════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ PRACTICE %02d:%02d:%02d                                             %20s Grand Prix ║\n",
                (int)((int)((now-start)*speed)/60)/60,
                (int)((now-start)*speed)/60-((int)(((int)((now-start)*speed)/60)/60)*60),
                (int)((now-start)*speed)-((int)(((now-start)*speed)/60)*60),
                gp.location);
    printf("╠══╦════════════════╦═══╦═════════════╦══════════╦══════════╦════╦════════╦════════╦════════╦═╦═╣\n");
    printf("║%2s│%16s│%3s│%13s║ %8s │ %8s │%4s║%8s│%8s│%8s│%s│%s║\n","/","driver","num","team","best lap","diff","laps","best S1","best S2","best S3","P","O");
    printf("╠══╬════════════════╬═══╬═════════════╬══════════╬══════════╬════╬════════╬════════╬════════╬═╬═╣\n");
    for (i=0;i<len_cars;i++)
    {
        if (data[order[i]] > 0){
            printf("║%2d│%16s│%3d│%13s║ %2d:%06.3f│ %2d:%06.3f│%3d ║%8.3f│%8.3f│%8.3f│%s│%s║\n",
                i+1,
                cars[order[i]].driver,
                cars[order[i]].number,
                cars[order[i]].team,

                (int)data[order[i]]/60,
                data[order[i]]-((int)data[order[i]]/60)*60,

                i > 0 ? (int)(data[order[i]]-data[order[i-1]])/60 : 0,
                i > 0 ? (data[order[i]]-data[order[i-1]])-((int)(data[order[i]]-data[order[i-1]])/60)*60 : 0,

                (int)data[10*(len_cars+1)+order[i]],
                data[s1*(len_cars+1)+order[i]],
                data[s2*(len_cars+1)+order[i]],
                data[s3*(len_cars+1)+order[i]],
                cars[order[i]].is_pit == true ? "P" : " ",
                cars[order[i]].is_out == true ? "O" : " ");
        } else {
            printf("║%2d│%16s│%3d│%13s║   ----   │   ----   │%3d ║  ----  │  ----  │  ----  │%s│%s║\n",
                i+1,
                cars[order[i]].driver,
                cars[order[i]].number,
                cars[order[i]].team,
                (int)data[10*(len_cars+1)+order[i]],
                cars[order[i]].is_pit == true ? "P" : " ",
                cars[order[i]].is_out == true ? "O" : " ");
        }
    }
    printf("╚══╩════════════════╩═══╩═════════════╩══════════╩══════════╩════╬════════╬════════╬════════╬═╩═╝\n");
    printf("                                                      best sector║%8.3f│%8.3f│%8.3f║\n",
        data[s1*(len_cars+1)+order_s1[0]],
        data[s2*(len_cars+1)+order_s2[0]],
        data[s3*(len_cars+1)+order_s3[0]]);
    printf("                                                          num/pos║%-4d%4d│%-4d%4d│%-4d%4d║\n",
        cars[order_s1[0]].number,order_s1[0]+1,
        cars[order_s2[0]].number,order_s2[0]+1,
        cars[order_s3[0]].number,order_s3[0]+1);
    printf("                                                                 ╚════════╩════════╩════════╝\n");

    free(order);
    free(order_s1);
    free(order_s2);
    free(order_s3);
}

void scoreboard_qualif_1(int len_cars, struct Car* cars, float* data, struct GrandPrix gp,int now,int start)
{
    int* order = sort(data+(q1*(len_cars+1)));
    int* order_s1 = sort(data+(s1*(len_cars+1)));
    int* order_s2 = sort(data+(s2*(len_cars+1)));
    int* order_s3 = sort(data+(s3*(len_cars+1)));
    int i;
    printf("╔═══════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ QUALIFICATIONS ROUND 1 %02d:%02d:%02d                               %20s Grand Prix ║\n",
                (int)((int)((now-start)*speed)/60)/60,
                (int)((now-start)*speed)/60-((int)(((int)((now-start)*speed)/60)/60)*60),
                (int)((now-start)*speed)-((int)(((now-start)*speed)/60)*60),
                gp.location);
    printf("╠══╦════════════════╦═══╦═════════════╦══════════╦══════════╦════╦════════╦════════╦════════╦═╦═╣\n");
    printf("║%2s│%16s│%3s│%13s║ %8s │ %8s │%4s║%8s│%8s│%8s│%s│%s║\n","/","driver","num","team","Q1","diff","laps","best S1","best S2","best S3","P","O");
    printf("╠══╬════════════════╬═══╬═════════════╬══════════╬══════════╬════╬════════╬════════╬════════╬═╬═╣\n");
    for (i=0;i<len_cars;i++)
    {
        if (data[order[i]+(q1*(len_cars+1))] > 0){
            printf("║%2d│%16s│%3d│%13s║ %2d:%06.3f│ %2d:%06.3f│%3d ║%8.3f│%8.3f│%8.3f│%s│%s║\n",
                i+1,
                cars[order[i]].driver,
                cars[order[i]].number,
                cars[order[i]].team,

                (int)data[order[i]+(q1*(len_cars+1))]/60,
                data[order[i]+(q1*(len_cars+1))]-((int)data[order[i]+(q1*(len_cars+1))]/60)*60,

                i > 0 ? (int)(data[order[i]+(q1*(len_cars+1))]-data[order[i-1]+(q1*(len_cars+1))])/60 : 0,
                i > 0 ? (data[order[i]+(q1*(len_cars+1))]-data[order[i-1]+(q1*(len_cars+1))])-((int)(data[order[i]+(q1*(len_cars+1))]-data[order[i-1]+(q1*(len_cars+1))])/60)*60 : 0,

                (int)data[lpc*(len_cars+1)+order[i]],
                data[s1*(len_cars+1)+order[i]],
                data[s2*(len_cars+1)+order[i]],
                data[s3*(len_cars+1)+order[i]],
                cars[order[i]].is_pit == true ? "P" : " ",
                cars[order[i]].is_out == true ? "O" : " ");
        } else {
            printf("║%2d│%16s│%3d│%13s║   ----   │   ----   │%3d ║  ----  │  ----  │  ----  │%s│%s║\n",
                i+1,
                cars[order[i]].driver,
                cars[order[i]].number,
                cars[order[i]].team,
                (int)data[lpc*(len_cars+1)+order[i]],
                cars[order[i]].is_pit == true ? "P" : " ",
                cars[order[i]].is_out == true ? "O" : " ");
        }
    }
    printf("╚══╩════════════════╩═══╩═════════════╩══════════╩══════════╩════╬════════╬════════╬════════╬═╩═╝\n");
    printf("                                                      best sector║%8.3f│%8.3f│%8.3f║\n",
        data[s1*(len_cars+1)+order_s1[0]],
        data[s2*(len_cars+1)+order_s2[0]],
        data[s3*(len_cars+1)+order_s3[0]]);
    printf("                                                          num/pos║%-4d%4d│%-4d%4d│%-4d%4d║\n",
        cars[order_s1[0]].number,order_s1[0]+1,
        cars[order_s2[0]].number,order_s2[0]+1,
        cars[order_s3[0]].number,order_s3[0]+1);
    printf("                                                                 ╚════════╩════════╩════════╝\n");

    free(order);
    free(order_s1);
    free(order_s2);
    free(order_s3);
}

void scoreboard_qualif_2(int len_cars, struct Car* cars, float* data, struct GrandPrix gp,int now,int start)
{
    int* order = sort(data+(q2*(len_cars+1)));
    int* order_s1 = sort(data+(s1*(len_cars+1)));
    int* order_s2 = sort(data+(s2*(len_cars+1)));
    int* order_s3 = sort(data+(s3*(len_cars+1)));
    int i;
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ QUALIFICATIONS ROUND 2 %02d:%02d:%02d                                         %20s Grand Prix  ║\n",
                (int)((int)((now-start)*speed)/60)/60,
                (int)((now-start)*speed)/60-((int)(((int)((now-start)*speed)/60)/60)*60),
                (int)((now-start)*speed)-((int)(((now-start)*speed)/60)*60),
                gp.location);
    printf("╠══╦════════════════╦═══╦═════════════╦══════════╦══════════╦══════════╦════╦════════╦════════╦════════╦═╦═╣\n");
    printf("║%2s│%16s│%3s│%13s║ %8s │ %8s │ %8s │%4s║%8s│%8s│%8s│%s│%s║\n","/","driver","num","team","Q1","Q2","diff","laps","best S1","best S2","best S3","P","O");
    printf("╠══╬════════════════╬═══╬═════════════╬══════════╬══════════╬══════════╬════╬════════╬════════╬════════╬═╬═╣\n");
    for (i=0;i<len_cars;i++)
    {
        if (data[order[i]+(q2*(len_cars+1))] > 0){
            printf("║%2d│%16s│%3d│%13s║ %2d:%06.3f│ %2d:%06.3f│ %2d:%06.3f│%3d ║%8.3f│%8.3f│%8.3f│%s│%s║\n",
                i+1,
                cars[order[i]].driver,
                cars[order[i]].number,
                cars[order[i]].team,

                (int)data[order[i]+(q1*(len_cars+1))]/60,
                data[order[i]+(q1*(len_cars+1))]-((int)data[order[i]+(q1*(len_cars+1))]/60)*60,

                (int)data[order[i]+(q2*(len_cars+1))]/60,
                data[order[i]+(q2*(len_cars+1))]-((int)data[order[i]+(q2*(len_cars+1))]/60)*60,

                i > 0 ? (int)(data[order[i]+(q2*(len_cars+1))]-data[order[i-1]+(q2*(len_cars+1))])/60 : 0,
                i > 0 ? (data[order[i]+(q2*(len_cars+1))]-data[order[i-1]+(q2*(len_cars+1))])-((int)(data[order[i]+(q2*(len_cars+1))]-data[order[i-1]+(q2*(len_cars+1))])/60)*60 : 0,

                (int)data[lpc*(len_cars+1)+order[i]],
                data[s1*(len_cars+1)+order[i]],
                data[s2*(len_cars+1)+order[i]],
                data[s3*(len_cars+1)+order[i]],
                cars[order[i]].is_pit == true ? "P" : " ",
                cars[order[i]].is_out == true ? "O" : " ");
        } else {
            printf("║%2d│%16s│%3d│%13s║ %2d:%06.3f│   ----   │   ----   │%3d ║  ----  │  ----  │  ----  │%s│%s║\n",
                    i+1,
                    cars[(int)data[(srt*(len_cars+1))+i]].driver,
                    cars[(int)data[(srt*(len_cars+1))+i]].number,
                    cars[(int)data[(srt*(len_cars+1))+i]].team,

                    (int)data[(int)data[(srt*(len_cars+1))+i]+(q1*(len_cars+1))]/60,
                    data[(int)data[(srt*(len_cars+1))+i]+(q1*(len_cars+1))]-((int)data[(int)data[(srt*(len_cars+1))+i]+(q1*(len_cars+1))]/60)*60,

                    (int)data[lpc*(len_cars+1)+order[i]],
                    cars[(int)data[(srt*(len_cars+1))+i]].is_pit == true ? "P" : " ",
                    cars[(int)data[(srt*(len_cars+1))+i]].is_out == true ? "O" : " ");
        }
    }
    printf("╚══╩════════════════╩═══╩═════════════╩══════════╩══════════╩══════════╩════╬════════╬════════╬════════╬═╩═╝\n");
    printf("                                                                 best sector║%8.3f│%8.3f│%8.3f║\n",
        data[s1*(len_cars+1)+order_s1[0]],
        data[s2*(len_cars+1)+order_s2[0]],
        data[s3*(len_cars+1)+order_s3[0]]);
    printf("                                                                     num/pos║%-4d%4d│%-4d%4d│%-4d%4d║\n",
        cars[order_s1[0]].number,order_s1[0]+1,
        cars[order_s2[0]].number,order_s2[0]+1,
        cars[order_s3[0]].number,order_s3[0]+1);
    printf("                                                                            ╚════════╩════════╩════════╝\n");

    free(order);
    free(order_s1);
    free(order_s2);
    free(order_s3);
}

void scoreboard_qualif_3(int len_cars, struct Car* cars, float* data, struct GrandPrix gp,int now,int start)
{
    int* order = sort(data+(q3*(len_cars+1)));
    int* order_s1 = sort(data+(s1*(len_cars+1)));
    int* order_s2 = sort(data+(s2*(len_cars+1)));
    int* order_s3 = sort(data+(s3*(len_cars+1)));
    int i;
    printf("╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ QUALIFICATIONS ROUND 3 %02d:%02d:%02d                                                     %20s Grand Prix ║\n",
                (int)((int)((now-start)*speed)/60)/60,
                (int)((now-start)*speed)/60-((int)(((int)((now-start)*speed)/60)/60)*60),
                (int)((now-start)*speed)-((int)(((now-start)*speed)/60)*60),
                gp.location);
    printf("╠══╦════════════════╦═══╦═════════════╦══════════╦══════════╦══════════╦══════════╦════╦════════╦════════╦════════╦═╦═╣\n");
    printf("║%2s│%16s│%3s│%13s║ %8s │ %8s │ %8s │ %8s │%4s║%8s│%8s│%8s│%s│%s║\n","/","driver","num","team","Q1","Q2","Q3","diff","laps","best S1","best S2","best S3","P","O");
    printf("╠══╬════════════════╬═══╬═════════════╬══════════╬══════════╬══════════╬══════════╬════╬════════╬════════╬════════╬═╬═╣\n");
    for (i=0;i<len_cars;i++)
    {
        if (data[order[i]+(q3*(len_cars+1))] > 0){
            printf("║%2d│%16s│%3d│%13s║ %2d:%06.3f│ %2d:%06.3f│ %2d:%06.3f│ %2d:%06.3f│%3d ║%8.3f│%8.3f│%8.3f│%s│%s║\n",
                i+1,
                cars[order[i]].driver,
                cars[order[i]].number,
                cars[order[i]].team,

                (int)data[order[i]+(q1*(len_cars+1))]/60,
                data[order[i]+(q1*(len_cars+1))]-((int)data[order[i]+(q1*(len_cars+1))]/60)*60,

                (int)data[order[i]+(q2*(len_cars+1))]/60,
                data[order[i]+(q2*(len_cars+1))]-((int)data[order[i]+(q2*(len_cars+1))]/60)*60,

                (int)data[order[i]+(q3*(len_cars+1))]/60,
                data[order[i]+(q3*(len_cars+1))]-((int)data[order[i]+(q3*(len_cars+1))]/60)*60,

                i > 0 ? (int)(data[order[i]+(q3*(len_cars+1))]-data[order[i-1]+(q3*(len_cars+1))])/60 : 0,
                i > 0 ? (data[order[i]+(q3*(len_cars+1))]-data[order[i-1]+(q3*(len_cars+1))])-((int)(data[order[i]+(q3*(len_cars+1))]-data[order[i-1]+(q3*(len_cars+1))])/60)*60 : 0,


                (int)data[lpc*(len_cars+1)+order[i]],
                data[s1*(len_cars+1)+order[i]],
                data[s2*(len_cars+1)+order[i]],
                data[s3*(len_cars+1)+order[i]],
                cars[order[i]].is_pit == true ? "P" : " ",
                cars[order[i]].is_out == true ? "O" : " ");
        } else if (cars[(int)data[(srt*(len_cars+1))+i]].is_out_q2 == true){
            printf("║%2d│%16s│%3d│%13s║ %2d:%06.3f│   ----   │   ----   │   ----   │%3d ║  ----  │  ----  │  ----  │%s│%s║\n",
                i+1,
                cars[(int)data[(srt*(len_cars+1))+i]].driver,
                cars[(int)data[(srt*(len_cars+1))+i]].number,
                cars[(int)data[(srt*(len_cars+1))+i]].team,

                (int)data[(int)data[(srt*(len_cars+1))+i]+(q1*(len_cars+1))]/60,
                data[(int)data[(srt*(len_cars+1))+i]+(q1*(len_cars+1))]-((int)data[(int)data[(srt*(len_cars+1))+i]+(q1*(len_cars+1))]/60)*60,


                (int)data[lpc*(len_cars+1)+order[i]],
                cars[(int)data[(srt*(len_cars+1))+i]].is_pit == true ? "P" : " ",
                cars[(int)data[(srt*(len_cars+1))+i]].is_out == true ? "O" : " ");
        } else {
            printf("║%2d│%16s│%3d│%13s║ %2d:%06.3f│ %2d:%06.3f│   ----   │   ----   │%3d ║  ----  │  ----  │  ----  │%s│%s║\n",
                i+1,
                cars[(int)data[(srt*(len_cars+1))+i]].driver,
                cars[(int)data[(srt*(len_cars+1))+i]].number,
                cars[(int)data[(srt*(len_cars+1))+i]].team,

                (int)data[(int)data[(srt*(len_cars+1))+i]+(q1*(len_cars+1))]/60,
                data[(int)data[(srt*(len_cars+1))+i]+(q1*(len_cars+1))]-((int)data[(int)data[(srt*(len_cars+1))+i]+(q1*(len_cars+1))]/60)*60,

                (int)data[(int)data[(srt*(len_cars+1))+i]+(q2*(len_cars+1))]/60,
                data[(int)data[(srt*(len_cars+1))+i]+(q2*(len_cars+1))]-((int)data[(int)data[(srt*(len_cars+1))+i]+(q2*(len_cars+1))]/60)*60,


                (int)data[lpc*(len_cars+1)+order[i]],
                cars[(int)data[(srt*(len_cars+1))+i]].is_pit == true ? "P" : " ",
                cars[(int)data[(srt*(len_cars+1))+i]].is_out == true ? "O" : " ");
        }
    }
    printf("╚══╩════════════════╩═══╩═════════════╩══════════╩══════════╩══════════╩══════════╩════╬════════╬════════╬════════╬═╩═╝\n");
    printf("                                                                            best sector║%8.3f│%8.3f│%8.3f║\n",
        data[s1*(len_cars+1)+order_s1[0]],
        data[s2*(len_cars+1)+order_s2[0]],
        data[s3*(len_cars+1)+order_s3[0]]);
    printf("                                                                                num/pos║%-4d%4d│%-4d%4d│%-4d%4d║\n",
        cars[order_s1[0]].number,order_s1[0]+1,
        cars[order_s2[0]].number,order_s2[0]+1,
        cars[order_s3[0]].number,order_s3[0]+1);
    printf("                                                                                       ╚════════╩════════╩════════╝\n");

    free(order);
    free(order_s1);
    free(order_s2);
    free(order_s3);
}

void scoreboard_sprint(int len_cars, struct Car* cars, float* data, struct GrandPrix gp,int now,int start)
{
    int* order = sort(data+(sti*(len_cars+1)));
    int* order_s1 = sort(data+(s1*(len_cars+1)));
    int* order_s2 = sort(data+(s2*(len_cars+1)));
    int* order_s3 = sort(data+(s3*(len_cars+1)));
    int* order_lp = sort(data+(rlp*(len_cars+1)));
    int i;
    printf("╔═══════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ SPRINT %02d:%02d:%02d                                              %20s  Grand Prix ║\n",
                (int)((int)((now-start)*speed)/60)/60,
                (int)((now-start)*speed)/60-((int)(((int)((now-start)*speed)/60)/60)*60),
                (int)((now-start)*speed)-((int)(((now-start)*speed)/60)*60),
                gp.location);
    printf("╠══╦════════════════╦═══╦═════════════╦══════════╦══════════╦════╦════════╦════════╦════════╦═╦═╣\n");
    printf("║%2s│%16s│%3s│%13s║ %8s │ %8s │%4s║%8s│%8s│%8s│%s│%s║\n","/","driver","num","team","time","diff","laps","best S1","best S2","best S3","P","O");
    printf("╠══╬════════════════╬═══╬═════════════╬══════════╬══════════╬════╬════════╬════════╬════════╬═╬═╣\n");
    for (i=0;i<len_cars;i++)
    {
        if (data[order[i]+(sti*(len_cars+1))] > 0){
            printf("║%2d│%16s│%3d│%13s║ %2d:%06.3f│ %2d:%06.3f│%3d ║%8.3f│%8.3f│%8.3f│%s│%s║\n",
                i+1,
                cars[order[i]].driver,
                cars[order[i]].number,
                cars[order[i]].team,

                (int)data[order[i]+(sti*(len_cars+1))]/60,
                data[order[i]+(sti*(len_cars+1))]-((int)data[order[i]+(sti*(len_cars+1))]/60)*60,

                i > 0 ? (int)(data[order[i]+(sti*(len_cars+1))]-data[order[i-1]+(sti*(len_cars+1))])/60 : 0,
                i > 0 ? data[order[i]+(sti*(len_cars+1))]-data[order[i-1]+(sti*(len_cars+1))]-((int)(data[order[i]+(sti*(len_cars+1))]-data[order[i-1]+(sti*(len_cars+1))])/60)*60 : 0,

                (int)data[lpc*(len_cars+1)+order[i]],
                data[s1*(len_cars+1)+order[i]],
                data[s2*(len_cars+1)+order[i]],
                data[s3*(len_cars+1)+order[i]],
                cars[order[i]].is_pit == true ? "P" : " ",
                cars[order[i]].is_out == true ? "O" : " ");
        } else {
            printf("║%2d│%16s│%3d│%13s║   ----   │   ----   │%3d ║  ----  │  ----  │  ----  │%s│%s║\n",
                i+1,
                cars[order[i]].driver,
                cars[order[i]].number,
                cars[order[i]].team,
                (int)data[lpc*(len_cars+1)+order[i]],
                cars[order[i]].is_pit == true ? "P" : " ",
                cars[order[i]].is_out == true ? "O" : " ");
        }
    }
    printf("╚══╩════════════════╩═══╩═════════════╬══════════╬══════════╩════╬════════╬════════╬════════╬═╩═╝\n");
    printf("                              best lap║ %2d:%06.3f║    best sector║%8.3f│%8.3f│%8.3f║\n",
        (int)data[slp*(len_cars+1)+order_lp[0]]/60,
        data[slp*(len_cars+1)+order_lp[0]]-((int)(data[slp*(len_cars+1)+order_lp[0]]/60))*60,

        data[s1*(len_cars+1)+order_s1[0]],
        data[s2*(len_cars+1)+order_s2[0]],
        data[s3*(len_cars+1)+order_s3[0]]);
    printf("                               num/pos║%-4d  %4d║        num/pos║%-4d%4d│%-4d%4d│%-4d%4d║\n",
        cars[order_lp[0]].number,order_lp[0]+1,
        cars[order_s1[0]].number,order_s1[0]+1,
        cars[order_s2[0]].number,order_s2[0]+1,
        cars[order_s3[0]].number,order_s3[0]+1);
    printf("                                      ╚══════════╝               ╚════════╩════════╩════════╝\n");

    free(order);
    free(order_s1);
    free(order_s2);
    free(order_s3);
    free(order_lp);
}

void scoreboard_race(int len_cars, struct Car* cars, float* data, struct GrandPrix gp,int now,int start)
{
    int* order = sort(data+(rti*(len_cars+1)));
    int* order_s1 = sort(data+(s1*(len_cars+1)));
    int* order_s2 = sort(data+(s2*(len_cars+1)));
    int* order_s3 = sort(data+(s3*(len_cars+1)));
    int* order_lp = sort(data+(rlp*(len_cars+1)));
    int i;
    printf("╔═══════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ RACE %02d:%02d:%02d                                                %20s  Grand Prix ║\n",
                (int)((int)((now-start)*speed)/60)/60,
                (int)((now-start)*speed)/60-((int)(((int)((now-start)*speed)/60)/60)*60),
                (int)((now-start)*speed)-((int)(((now-start)*speed)/60)*60),
                gp.location);
    printf("╠══╦════════════════╦═══╦═════════════╦══════════╦══════════╦════╦════════╦════════╦════════╦═╦═╣\n");
    printf("║%2s│%16s│%3s│%13s║ %8s │ %8s │%4s║%8s│%8s│%8s│%s│%s║\n","/","driver","num","team","time","diff","laps","best S1","best S2","best S3","P","O");
    printf("╠══╬════════════════╬═══╬═════════════╬══════════╬══════════╬════╬════════╬════════╬════════╬═╬═╣\n");
    for (i=0;i<len_cars;i++)
    {
        if (data[order[i]+(rti*(len_cars+1))] > 0){
            printf("║%2d│%16s│%3d│%13s║ %2d:%06.3f│ %2d:%06.3f│%3d ║%8.3f│%8.3f│%8.3f│%s│%s║\n",
                i+1,
                cars[order[i]].driver,
                cars[order[i]].number,
                cars[order[i]].team,

                (int)data[order[i]+(rti*(len_cars+1))]/60,
                data[order[i]+(rti*(len_cars+1))]-((int)data[order[i]+(rti*(len_cars+1))]/60)*60,

                i > 0 ? (int)(data[order[i]+(rti*(len_cars+1))]-data[order[i-1]+(rti*(len_cars+1))])/60 : 0,
                i > 0 ? data[order[i]+(rti*(len_cars+1))]-data[order[i-1]+(rti*(len_cars+1))]-((int)(data[order[i]+(rti*(len_cars+1))]-data[order[i-1]+(rti*(len_cars+1))])/60)*60 : 0,

                (int)data[lpc*(len_cars+1)+order[i]],
                data[s1*(len_cars+1)+order[i]],
                data[s2*(len_cars+1)+order[i]],
                data[s3*(len_cars+1)+order[i]],
                cars[order[i]].is_pit == true ? "P" : " ",
                cars[order[i]].is_out == true ? "O" : " ");
        } else {
            printf("║%2d│%16s│%3d│%13s║   ----   │   ----   │%3d ║  ----  │  ----  │  ----  │%s│%s║\n",
                i+1,
                cars[order[i]].driver,
                cars[order[i]].number,
                cars[order[i]].team,
                (int)data[lpc*(len_cars+1)+order[i]],
                cars[order[i]].is_pit == true ? "P" : " ",
                cars[order[i]].is_out == true ? "O" : " ");
        }
    }
    printf("╚══╩════════════════╩═══╩═════════════╬══════════╬══════════╩════╬════════╬════════╬════════╬═╩═╝\n");
    printf("                              best lap║ %2d:%06.3f║    best sector║%8.3f│%8.3f│%8.3f║\n",
        (int)data[rlp*(len_cars+1)+order_lp[0]]/60,
        data[rlp*(len_cars+1)+order_lp[0]]-((int)(data[rlp*(len_cars+1)+order_lp[0]]/60))*60,

        data[s1*(len_cars+1)+order_s1[0]],
        data[s2*(len_cars+1)+order_s2[0]],
        data[s3*(len_cars+1)+order_s3[0]]);
    printf("                               num/pos║%-4d  %4d║        num/pos║%-4d%4d│%-4d%4d│%-4d%4d║\n",
        cars[order_lp[0]].number,order_lp[0]+1,
        cars[order_s1[0]].number,order_s1[0]+1,
        cars[order_s2[0]].number,order_s2[0]+1,
        cars[order_s3[0]].number,order_s3[0]+1);
    printf("                                      ╚══════════╝               ╚════════╩════════╩════════╝\n");

    free(order);
    free(order_s1);
    free(order_s2);
    free(order_s3);
    free(order_lp);
}

void scoreboard_recap(int len_cars, struct Car* cars, float* data, struct GrandPrix gp)
{
    int* order = sort(data+(rti*(len_cars+1)));
    int* order_q1 = sort(data+(q1*(len_cars+1)));
    int* order_q2 = sort(data+(q2*(len_cars+1)));
    int* order_q3 = sort(data+(q3*(len_cars+1)));
    int* order_slp = sort(data+(slp*(len_cars+1)));
    int* order_sti = sort(data+(sti*(len_cars+1)));
    int* order_rlp = sort(data+(rlp*(len_cars+1)));
    int i;
    printf("╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ FINAL RECAP                                                                                             %20s Grand Prix ║\n",
                gp.location);
    printf("╠══╦════════════════╦═══╦═════════════╦══════════╦══════════╦══════════╦══════════╦══════════╦══════════╦══════════╦══════════╦═══╦═══╦═══╣\n");
    printf("║%2s│%16s│%3s│%13s║%10s│%10s│%10s│%10s│%10s│%10s│%10s│%10s│%3s║%3s│%3s║\n","/","driver","num","team","best Q1 ","best Q2 ","best Q3 ","bestSprint","timeSprint","best Race","time Race","diff ","lap","pts","tot");
    printf("╠══╬════════════════╬═══╬═════════════╬══════════╬══════════╬══════════╬══════════╬══════════╬══════════╬══════════╬══════════╬═══╬═══╬═══╣\n");
    for (i=0;i<len_cars;i++)
    {
        if (data[order[i]+(sti*(len_cars+1))] > 0)
        {
            if (data[order[i]+(q3*(len_cars+1))] > 0)
            {
                printf("║%2d│%16s│%3d│%13s║ %2d:%06.3f│ %2d:%06.3f│ %2d:%06.3f│ %2d:%06.3f│ %2d:%06.3f│ %2d:%06.3f│ %2d:%06.3f│ %2d:%06.3f│%3d║%3d│%3d║\n",
                    i+1,cars[order[i]].driver,cars[order[i]].number,cars[order[i]].team,
                    (int)data[order[i]+(q1*(len_cars+1))]/60,data[order[i]+(q1*(len_cars+1))]-((int)data[order[i]+(q1*(len_cars+1))]/60)*60,
                    (int)data[order[i]+(q2*(len_cars+1))]/60,data[order[i]+(q2*(len_cars+1))]-((int)data[order[i]+(q2*(len_cars+1))]/60)*60,
                    (int)data[order[i]+(q3*(len_cars+1))]/60,data[order[i]+(q3*(len_cars+1))]-((int)data[order[i]+(q3*(len_cars+1))]/60)*60,
                    (int)data[order[i]+(slp*(len_cars+1))]/60,data[order[i]+(slp*(len_cars+1))]-((int)data[order[i]+(slp*(len_cars+1))]/60)*60,
                    (int)data[order[i]+(sti*(len_cars+1))]/60,data[order[i]+(sti*(len_cars+1))]-((int)data[order[i]+(sti*(len_cars+1))]/60)*60,
                    (int)data[order[i]+(rlp*(len_cars+1))]/60,data[order[i]+(rlp*(len_cars+1))]-((int)data[order[i]+(rlp*(len_cars+1))]/60)*60,
                    (int)data[order[i]+(rti*(len_cars+1))]/60,data[order[i]+(rti*(len_cars+1))]-((int)data[order[i]+(rti*(len_cars+1))]/60)*60,
                    i > 0 ? (int)(data[order[i]+(rti*(len_cars+1))]-data[order[i-1]+(rti*(len_cars+1))])/60 : 0,
                    i > 0 ? (data[order[i]+(rti*(len_cars+1))]-data[order[i-1]+(rti*(len_cars+1))])-((int)(data[order[i]+(rti*(len_cars+1))]-data[order[i-1]+(rti*(len_cars+1))])/60)*60 : 0,
                    (int)data[lpc*(len_cars+1)+order[i]],(int)data[order[i]+(pts*(len_cars+1))],cars[order[i]].points);
            } else if (data[order[i]+(q2*(len_cars+1))] > 0) {
                printf("║%2d│%16s│%3d│%13s║ %2d:%06.3f│ %2d:%06.3f│   ----   │ %2d:%06.3f│ %2d:%06.3f│ %2d:%06.3f│ %2d:%06.3f│ %2d:%06.3f│%3d║%3d│%3d║\n",
                    i+1,cars[order[i]].driver,cars[order[i]].number,cars[order[i]].team,
                    (int)data[order[i]+(q1*(len_cars+1))]/60,data[order[i]+(q1*(len_cars+1))]-((int)data[order[i]+(q1*(len_cars+1))]/60)*60,
                    (int)data[order[i]+(q2*(len_cars+1))]/60,data[order[i]+(q2*(len_cars+1))]-((int)data[order[i]+(q2*(len_cars+1))]/60)*60,
                    (int)data[order[i]+(slp*(len_cars+1))]/60,data[order[i]+(slp*(len_cars+1))]-((int)data[order[i]+(slp*(len_cars+1))]/60)*60,
                    (int)data[order[i]+(sti*(len_cars+1))]/60,data[order[i]+(sti*(len_cars+1))]-((int)data[order[i]+(sti*(len_cars+1))]/60)*60,
                    (int)data[order[i]+(rlp*(len_cars+1))]/60,data[order[i]+(rlp*(len_cars+1))]-((int)data[order[i]+(rlp*(len_cars+1))]/60)*60,
                    (int)data[order[i]+(rti*(len_cars+1))]/60,data[order[i]+(rti*(len_cars+1))]-((int)data[order[i]+(rti*(len_cars+1))]/60)*60,
                    i > 0 ? (int)(data[order[i]+(rti*(len_cars+1))]-data[order[i-1]+(rti*(len_cars+1))])/60 : 0,
                    i > 0 ? (data[order[i]+(rti*(len_cars+1))]-data[order[i-1]+(rti*(len_cars+1))])-((int)(data[order[i]+(rti*(len_cars+1))]-data[order[i-1]+(rti*(len_cars+1))])/60)*60 : 0,
                    (int)data[lpc*(len_cars+1)+order[i]],(int)data[order[i]+(pts*(len_cars+1))],cars[order[i]].points);
            } else if (data[order[i]+(q1*(len_cars+1))] > 0) {
                printf("║%2d│%16s│%3d│%13s║ %2d:%06.3f│   ----   │   ----   │ %2d:%06.3f│ %2d:%06.3f│ %2d:%06.3f│ %2d:%06.3f│ %2d:%06.3f│%3d║%3d│%3d║\n",
                    i+1,cars[order[i]].driver,cars[order[i]].number,cars[order[i]].team,
                    (int)data[order[i]+(q1*(len_cars+1))]/60,data[order[i]+(q1*(len_cars+1))]-((int)data[order[i]+(q1*(len_cars+1))]/60)*60,
                    (int)data[order[i]+(slp*(len_cars+1))]/60,data[order[i]+(slp*(len_cars+1))]-((int)data[order[i]+(slp*(len_cars+1))]/60)*60,
                    (int)data[order[i]+(sti*(len_cars+1))]/60,data[order[i]+(sti*(len_cars+1))]-((int)data[order[i]+(sti*(len_cars+1))]/60)*60,
                    (int)data[order[i]+(rlp*(len_cars+1))]/60,data[order[i]+(rlp*(len_cars+1))]-((int)data[order[i]+(rlp*(len_cars+1))]/60)*60,
                    (int)data[order[i]+(rti*(len_cars+1))]/60,data[order[i]+(rti*(len_cars+1))]-((int)data[order[i]+(rti*(len_cars+1))]/60)*60,
                    i > 0 ? (int)(data[order[i]+(rti*(len_cars+1))]-data[order[i-1]+(rti*(len_cars+1))])/60 : 0,
                    i > 0 ? (data[order[i]+(rti*(len_cars+1))]-data[order[i-1]+(rti*(len_cars+1))])-((int)(data[order[i]+(rti*(len_cars+1))]-data[order[i-1]+(rti*(len_cars+1))])/60)*60 : 0,
                    (int)data[lpc*(len_cars+1)+order[i]],(int)data[order[i]+(pts*(len_cars+1))],cars[order[i]].points);
            } else {
                printf("║%2d│%16s│%3d│%13s║   ----   │   ----   │   ----   │ %2d:%06.3f│ %2d:%06.3f│ %2d:%06.3f│ %2d:%06.3f│ %2d:%06.3f│%3d║%3d│%3d║\n",
                    i+1,cars[order[i]].driver,cars[order[i]].number,cars[order[i]].team,
                    (int)data[order[i]+(slp*(len_cars+1))]/60,data[order[i]+(slp*(len_cars+1))]-((int)data[order[i]+(slp*(len_cars+1))]/60)*60,
                    (int)data[order[i]+(sti*(len_cars+1))]/60,data[order[i]+(sti*(len_cars+1))]-((int)data[order[i]+(sti*(len_cars+1))]/60)*60,
                    (int)data[order[i]+(rlp*(len_cars+1))]/60,data[order[i]+(rlp*(len_cars+1))]-((int)data[order[i]+(rlp*(len_cars+1))]/60)*60,
                    (int)data[order[i]+(rti*(len_cars+1))]/60,data[order[i]+(rti*(len_cars+1))]-((int)data[order[i]+(rti*(len_cars+1))]/60)*60,
                    i > 0 ? (int)(data[order[i]+(rti*(len_cars+1))]-data[order[i-1]+(rti*(len_cars+1))])/60 : 0,
                    i > 0 ? (data[order[i]+(rti*(len_cars+1))]-data[order[i-1]+(rti*(len_cars+1))])-((int)(data[order[i]+(rti*(len_cars+1))]-data[order[i-1]+(rti*(len_cars+1))])/60)*60 : 0,
                    (int)data[lpc*(len_cars+1)+order[i]],(int)data[order[i]+(pts*(len_cars+1))],cars[order[i]].points);
            }
        } else {
            if (data[order[i]+(q3*(len_cars+1))] > 0)
            {
                printf("║%2d│%16s│%3d│%13s║ %2d:%06.3f│ %2d:%06.3f│ %2d:%06.3f│   ----   │   ----   │ %2d:%06.3f│ %2d:%06.3f│ %2d:%06.3f│%3d║%3d│%3d║\n",
                    i+1,cars[order[i]].driver,cars[order[i]].number,cars[order[i]].team,
                    (int)data[order[i]+(q1*(len_cars+1))]/60,data[order[i]+(q1*(len_cars+1))]-((int)data[order[i]+(q1*(len_cars+1))]/60)*60,
                    (int)data[order[i]+(q2*(len_cars+1))]/60,data[order[i]+(q2*(len_cars+1))]-((int)data[order[i]+(q2*(len_cars+1))]/60)*60,
                    (int)data[order[i]+(q3*(len_cars+1))]/60,data[order[i]+(q3*(len_cars+1))]-((int)data[order[i]+(q3*(len_cars+1))]/60)*60,
                    (int)data[order[i]+(rlp*(len_cars+1))]/60,data[order[i]+(rlp*(len_cars+1))]-((int)data[order[i]+(rlp*(len_cars+1))]/60)*60,
                    (int)data[order[i]+(rti*(len_cars+1))]/60,data[order[i]+(rti*(len_cars+1))]-((int)data[order[i]+(rti*(len_cars+1))]/60)*60,
                    i > 0 ? (int)(data[order[i]+(rti*(len_cars+1))]-data[order[i-1]+(rti*(len_cars+1))])/60 : 0,
                    i > 0 ? (data[order[i]+(rti*(len_cars+1))]-data[order[i-1]+(rti*(len_cars+1))])-((int)(data[order[i]+(rti*(len_cars+1))]-data[order[i-1]+(rti*(len_cars+1))])/60)*60 : 0,
                    (int)data[lpc*(len_cars+1)+order[i]],(int)data[order[i]+(pts*(len_cars+1))],cars[order[i]].points);
            } else if (data[order[i]+(q2*(len_cars+1))] > 0) {
                printf("║%2d│%16s│%3d│%13s║ %2d:%06.3f│ %2d:%06.3f│   ----   │   ----   │   ----   │ %2d:%06.3f│ %2d:%06.3f│ %2d:%06.3f│%3d║%3d│%3d║\n",
                    i+1,cars[order[i]].driver,cars[order[i]].number,cars[order[i]].team,
                    (int)data[order[i]+(q1*(len_cars+1))]/60,data[order[i]+(q1*(len_cars+1))]-((int)data[order[i]+(q1*(len_cars+1))]/60)*60,
                    (int)data[order[i]+(q2*(len_cars+1))]/60,data[order[i]+(q2*(len_cars+1))]-((int)data[order[i]+(q2*(len_cars+1))]/60)*60,
                    (int)data[order[i]+(rlp*(len_cars+1))]/60,data[order[i]+(rlp*(len_cars+1))]-((int)data[order[i]+(rlp*(len_cars+1))]/60)*60,
                    (int)data[order[i]+(rti*(len_cars+1))]/60,data[order[i]+(rti*(len_cars+1))]-((int)data[order[i]+(rti*(len_cars+1))]/60)*60,
                    i > 0 ? (int)(data[order[i]+(rti*(len_cars+1))]-data[order[i-1]+(rti*(len_cars+1))])/60 : 0,
                    i > 0 ? (data[order[i]+(rti*(len_cars+1))]-data[order[i-1]+(rti*(len_cars+1))])-((int)(data[order[i]+(rti*(len_cars+1))]-data[order[i-1]+(rti*(len_cars+1))])/60)*60 : 0,
                    (int)data[lpc*(len_cars+1)+order[i]],(int)data[order[i]+(pts*(len_cars+1))],cars[order[i]].points);
            } else if (data[order[i]+(q1*(len_cars+1))] > 0) {
                printf("║%2d│%16s│%3d│%13s║ %2d:%06.3f│   ----   │   ----   │   ----   │   ----   │ %2d:%06.3f│ %2d:%06.3f│ %2d:%06.3f│%3d║%3d│%3d║\n",
                    i+1,cars[order[i]].driver,cars[order[i]].number,cars[order[i]].team,
                    (int)data[order[i]+(q1*(len_cars+1))]/60,data[order[i]+(q1*(len_cars+1))]-((int)data[order[i]+(q1*(len_cars+1))]/60)*60,
                    (int)data[order[i]+(rlp*(len_cars+1))]/60,data[order[i]+(rlp*(len_cars+1))]-((int)data[order[i]+(rlp*(len_cars+1))]/60)*60,
                    (int)data[order[i]+(rti*(len_cars+1))]/60,data[order[i]+(rti*(len_cars+1))]-((int)data[order[i]+(rti*(len_cars+1))]/60)*60,
                    i > 0 ? (int)(data[order[i]+(rti*(len_cars+1))]-data[order[i-1]+(rti*(len_cars+1))])/60 : 0,
                    i > 0 ? (data[order[i]+(rti*(len_cars+1))]-data[order[i-1]+(rti*(len_cars+1))])-((int)(data[order[i]+(rti*(len_cars+1))]-data[order[i-1]+(rti*(len_cars+1))])/60)*60 : 0,
                    (int)data[lpc*(len_cars+1)+order[i]],(int)data[order[i]+(pts*(len_cars+1))],cars[order[i]].points);
            } else {
                if (data[order[i]+(rti*(len_cars+1))] > 0) {
                    printf("║%2d│%16s│%3d│%13s║   ----   │   ----   │   ----   │   ----   │   ----   │ %2d:%06.3f│ %2d:%06.3f│ %2d:%06.3f│%3d║%3d│%3d║\n",
                        i+1,cars[order[i]].driver,cars[order[i]].number,cars[order[i]].team,
                        (int)data[order[i]+(rlp*(len_cars+1))]/60,data[order[i]+(rlp*(len_cars+1))]-((int)data[order[i]+(rlp*(len_cars+1))]/60)*60,
                        (int)data[order[i]+(rti*(len_cars+1))]/60,data[order[i]+(rti*(len_cars+1))]-((int)data[order[i]+(rti*(len_cars+1))]/60)*60,
                        i > 0 ? (int)(data[order[i]+(rti*(len_cars+1))]-data[order[i-1]+(rti*(len_cars+1))])/60 : 0,
                        i > 0 ? (data[order[i]+(rti*(len_cars+1))]-data[order[i-1]+(rti*(len_cars+1))])-((int)(data[order[i]+(rti*(len_cars+1))]-data[order[i-1]+(rti*(len_cars+1))])/60)*60 : 0,
                        (int)data[lpc*(len_cars+1)+order[i]],(int)data[order[i]+(pts*(len_cars+1))],cars[order[i]].points);
                } else {
                        printf("║%2d│%16s│%3d│%13s║   ----   │   ----   │   ----   │   ----   │   ----   │   ----   │   ----   │   ----   │   ║   │%3d║\n",
                        i+1,cars[order[i]].driver,cars[order[i]].number,cars[order[i]].team,cars[order[i]].points);
                }
            }
        }
    }
    printf("╚══╩════════════════╩═══╩═════════════╬══════════╬══════════╬══════════╬══════════╬══════════╬══════════╬══════════╩══════════╩═══╩═══╩═══╝\n");
    printf("                                  best║ %2d:%06.3f│ %2d:%06.3f│ %2d:%06.3f│ %2d:%06.3f│ %2d:%06.3f│ %2d:%06.3f║\n",
        (int)data[q1*(len_cars+1)+order_q1[0]]/60,
        data[q1*(len_cars+1)+order_q1[0]]-((int)(data[q1*(len_cars+1)+order_q1[0]]/60))*60,

        (int)data[q2*(len_cars+1)+order_q2[0]]/60,
        data[q2*(len_cars+1)+order_q2[0]]-((int)(data[q2*(len_cars+1)+order_q2[0]]/60))*60,

        (int)data[q3*(len_cars+1)+order_q3[0]]/60,
        data[q3*(len_cars+1)+order_q3[0]]-((int)(data[q3*(len_cars+1)+order_q3[0]]/60))*60,

        (int)data[slp*(len_cars+1)+order_slp[0]]/60,
        data[slp*(len_cars+1)+order_slp[0]]-((int)(data[slp*(len_cars+1)+order_slp[0]]/60))*60,

        (int)data[sti*(len_cars+1)+order_sti[0]]/60,
        data[sti*(len_cars+1)+order_sti[0]]-((int)(data[sti*(len_cars+1)+order_sti[0]]/60))*60,

        (int)data[rlp*(len_cars+1)+order_rlp[0]]/60,
        data[rlp*(len_cars+1)+order_rlp[0]]-((int)(data[rlp*(len_cars+1)+order_rlp[0]]/60))*60);
    printf("                               num/pos║%-4d  %4d│%-4d  %4d│%-4d  %4d│%-4d  %4d│%-4d  %4d│%-4d  %4d║\n",
        cars[order_q1[0]].number,order_q1[0]+1,
        cars[order_q2[0]].number,order_q2[0]+1,
        cars[order_q2[0]].number,order_q2[0]+1,
        cars[order_slp[0]].number,order_slp[0]+1,
        cars[order_sti[0]].number,order_sti[0]+1,
        cars[order_rlp[0]].number,order_rlp[0]+1);
    printf("                                      ╚══════════╩══════════╩══════════╩══════════╩══════════╩══════════╝\n");

    free(order);
    free(order_q1);
    free(order_q2);
    free(order_q3);
    free(order_slp);
    free(order_sti);
    free(order_rlp);
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
                printf("Practices are over\nsave scores to file? [y/n]:\n");
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
                printf("Round 1 of Qualifications are over\nsave scores to file? [y/n]:\n");
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
                printf("Round 2 of Qualifications are over\nsave scores to file? [y/n]:\n");
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
                printf("Round 3 of Qualifications are over\nsave scores to file? [y/n]:\n");
                gps[gp].GP_state = 0;
                break;

            case 5: // sprint
                system("clear");
                now = time(NULL);
                scoreboard_sprint(len_cars,cars,data,gps[gp],now,start);
                break;

            case -5:
                system("clear");
                now = time(NULL);
                scoreboard_sprint(len_cars,cars,data,gps[gp],now,start);
                printf("The sprint is over\nsave scores to file? [y/n]:\n");
                gps[gp].GP_state = 0;
                break;

            case 6: // race
                system("clear");
                now = time(NULL);
                scoreboard_race(len_cars,cars,data,gps[gp],now,start);
                break;

            case -6:
                system("clear");
                now = time(NULL);
                scoreboard_race(len_cars,cars,data,gps[gp],now,start);
                printf("The race is over\nsave scores to file? [y/n]:\n");
                gps[gp].GP_state = 0;
                break;
            
            case 7:
                system("clear");
                scoreboard_recap(len_cars,cars,data,gps[gp]);
                gps[gp].GP_state = 0;
                break;
            
            case -7:
                system("clear");
                scoreboard_recap(len_cars,cars,data,gps[gp]);
                printf("save recap to file? [y/n]:\n");
                gps[gp].GP_state = 0;
                break;
                
            default:
                shmdt(cars);
                shmdt(gps);
                shmdt(data);
                exit(0);
        }
        sleep(1);
    }
}
