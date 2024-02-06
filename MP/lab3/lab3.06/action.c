#include "action.h"
int valid_datetime(const char *datetime)
{
    if (strlen(datetime) != 19)
    {
        return 0;
    }
    if (datetime[2] != ':' || datetime[5] != ':' || datetime[10] != ' ' || datetime[13] != ':' || datetime[16] != ':')
    {
        return 0;
    }
    int day = atoi(&datetime[0]);
    int month = atoi(&datetime[3]);
    int year = atoi(&datetime[6]);
    int hour = atoi(&datetime[11]);
    int minute = atoi(&datetime[14]);
    int second = atoi(&datetime[17]);

    if (day < 1 || day > 31 || month < 1 || month > 12 || hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59)
    {
        return 0;
    }
    // високосный год
    int leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    switch (month)
    {
    case 2: // Февраль
        if (leap && day > 29)
        {
            return 0;
        }
        else if (!leap && day > 28)
        {
            return 0;
        }
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        if (day > 30)
        {
            return 0;
        }
        break;
    }
    return 1;
}

check_data read_input(RouteNode **route, int count, char *files[])
{
    for (int i = 0; i < count; i++)
    {
        FILE *file = fopen(files[i], "r");
        if (!file)
        {
            return incorrect_data;
        }

        int x, y;
        fscanf(file, "%d %d", &x, &y);

        char number[INPUT];
        char stop_date[10];
        char stop_time[9];
        char departure_date[10];
        char departure_time[9];
        char marker[INPUT];
        Stops stop;
        while (fscanf(file, "%s %s %s %s %s %s", number, stop_date, stop_time, departure_date, departure_time, marker) != EOF)
        {
            char *datetime_stop = strcat(stop_date, " ");
            datetime_stop = strcat(datetime_stop, stop_time);
            char *datetime_departure = strcat(departure_date, " ");
            datetime_departure = strcat(datetime_departure, departure_time);

            if (valid_datetime(datetime_stop) && valid_datetime(datetime_departure))
            {
                strcpy(stop.number, number);
                strcpy(stop.stop_datetime, datetime_stop);
                strcpy(stop.departure_datetime, datetime_departure);
                strcpy(stop.marker, marker);
                stop.x = x;
                stop.y = y;
               
            }
            else
            {
                return incorrect_data;
            }
        }

        fclose(file);
    }

    return correct_data;
}
