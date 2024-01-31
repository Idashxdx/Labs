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
check_data add_stop_to_route(RouteNode **head, int x, int y, Stops stop)
{
    RouteNode *newRouteNode = (RouteNode *)malloc(sizeof(RouteNode));
    newRouteNode->next = NULL;
    StopNode *newStopNode = (StopNode *)malloc(sizeof(StopNode));
    newStopNode->value = stop;
    newStopNode->next = NULL;
    newStopNode->value.x = x;
    newStopNode->value.y = y;
    newRouteNode->route = newStopNode;
    newRouteNode->next = *head;
    *head = newRouteNode;

    return correct_data;
}
check_data read_input(RouteNode **head, int count, char *files[])
{
    for (int i = 0; i < count; i++)
    {
        FILE *file = fopen(files[i], "r");
        if (!file)
        {
            return incorrect_data;
        }

        int x, y;
        if (fscanf(file, "%d %d", &x, &y) != 2)
        {
            fclose(file);
            return incorrect_data;
        }

        Stops stop;
        while (fscanf(file, "%s %s %s %s", stop.number, stop.stop_time, stop.departure_time, stop.marker) == 4)
        {
            if (!valid_datetime(stop.stop_time) || !valid_datetime(stop.departure_time))
            {
                return incorrect_data;
            }
            check_data result = add_stop_to_route(head, x, y, stop);
            if (result != correct_data)
            {
                fclose(file);
                return result;
            }
        }
        fclose(file);
    }
    return correct_data;
}

