
#ifndef action_h
#define action_h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define INPUT 50
typedef enum check_data
{
    correct_data,
    incorrect_data,
    memory_alloc_error
} check_data;

// Остановка
typedef struct
{
    char number[INPUT];
    char stop_time[20];
    char departure_time[20];
    char marker[INPUT];
    int x; // coord.
    int y;
} Stops;
typedef struct StopNode
{
    Stops value;
    struct StopNode *next;
} StopNode;
typedef struct RouteNode
{
    StopNode route;
    struct RouteNode *next;
} RouteNode;
int valid_datetime(const char *datetime);
check_data add_stop_to_route(RouteNode **head, int x, int y, Stops stop);
check_data read_input(RouteNode **head, int count, char *files[]);
void print_stops(StopNode *head);
void free_route(RouteNode *head);
#endif