void wipe_data(float* data, int len_cars)
{
    int i;
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
}

void wipe_data_segment(float* data)
{
    int i;
    for (i = 0; data[i] != end; i++)
    {
        data[i] = 0;
    }
}

void save_data(struct GrandPrix* gps, struct Car* cars, float* data, int gp, int step)
{
    switch (step)
    {
    case 1:
        break;

    case 2:
        break;

    case 3:
        break;

    case 4:
        break;

    case 5:
        break;

    case 6:
        break;
    
    default:
        break;
    }
}