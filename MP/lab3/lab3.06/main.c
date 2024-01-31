#include "action.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Enter files input\n");
        return 1;
    }
    else
    {

        RouteNode *routes = NULL;
        // size_t count = 0;
        // size_t capacity = 2;
        switch (read_input(&routes, argc - 1, argv + 1))
        {
        case correct_data:
            printf("Files reading\n\n");
            RouteNode *current_route = routes;
                while (current_route != NULL) {
                    // Вывод информации о маршруте
                    printf("Route Information:\n");
                    print_stops(current_route->route);
                    current_route = current_route->next;
                }
                // Освобождение памяти занятой под списком маршрутов и остановок
                free_route(routes);
            break;
        case memory_alloc_error:
            printf("Memory allocation error\n");
            return 1;
        default:
            printf("Incorrect data in file\n");
            return 1;
        }

    }
    printf("M8O-211B-22  Mashrabova  lab3 tack6\n");
    return 0;
}
