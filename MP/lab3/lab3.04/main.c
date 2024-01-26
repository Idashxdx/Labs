#include "action.h"

int main(int argc, char *argv[])
{

    // TASK 1
    // план: создаем какую нибудь строку и создаем то что добавим(функции). Соединяем(функция). Выводим, чистим память (функция).
    printf("Mashrabova MP Lab 3 Task 4.1:\n\n");
    // 1. создания экземпляра типа String
    String str1;
    switch (create_string("qwerty ", &str1))
    {
    case correct_data:
        printf("str1 ---> %s; lenght ---> %d;\n\n", str1.str, str1.length);
        break;
    case memory_alloc_error:
        printf("Memory allocation error\n");
        return 1;
    default:
        printf("Incorrect data\n");
        return 1;
    }
    String str2;
    switch (create_string("ytrewq", &str2))
    {
    case correct_data:
        printf("str2 ---> %s; lenght ---> %d;\n\n", str2.str, str2.length);
        break;
    case memory_alloc_error:
        printf("Memory allocation error\n");
        return 1;
    default:
        printf("Incorrect data\n");
        return 1;
    }
    // 4. отношения эквивалентности между двумя экземплярами типа String
    if (equality(str1, str2) == 0)
    {
        printf("str1:%s and str2: %s ---> NOT Equivalents\n\n", str1.str, str2.str);
    }
    else
    {
        printf("str1:%s and str2: %s ---> Equivalents\n\n", str1.str, str2.str);
    }
    // 5.копирования содержимого экземпляра типа String в существующий экземпляр типа String
    switch (copy_string(&str1, str2))
    {
    case correct_data:
        printf("new str1 after copying str2 to str1 ---> %s;\n\n", str1.str);
        break;
    case memory_alloc_error:
        printf("Memory allocation error\n");
        return 1;
    default:
        printf("Incorrect data\n");
        return 1;
    }
    // 6. копирования содержимого экземпляра типа String в новый экземпляр типа String, размещённый в динамической памяти
    String str3;
    switch (copy_to_dinamic_string(str1, &str3))
    {
    case correct_data:
        printf("new str3 after copying str1 to dynamic memory ---> %s;\n\n", str3.str);
        break;
    case memory_alloc_error:
        printf("Memory allocation error\n");
        return 1;
    default:
        printf("Incorrect data\n");
        return 1;
    }
    // 3. отношения порядка между двумя экземплярами типа String
    // сравниваем длину, потом буквы - если размер одинаковый, при сравнении букв если по алфавиту раньше - то строка1 меньше строки2
    if (compare_string(str1, str2) > 0)
    {
        printf("str1:%s MORE str2: %s\n\n", str1.str, str2.str);
    }
    else if (compare_string(str1, str2) < 0)
    {
        printf("str1:%s LESS str2: %s\n\n", str1.str, str2.str);
    }
    else
    {
        printf("str1:%s EQUAL str2: %s\n\n", str1.str, str2.str);
    }
    // 7. конкатенации к содержимому первого экземпляра типа String содержимого второго экземпляра типа String.
    switch (concatenation_string(&str1, str2))
    {
    case correct_data:
        printf("new str1 after concatenation of str1 and str2 ---> %s;\n\n", str1.str);
        break;
    case memory_alloc_error:
        printf("Memory allocation error\n");
        return 1;
    default:
        printf("Incorrect data\n");
        return 1;
    }
    // 2.удаления внутреннего содержимого экземпляра типа String
    clear_string(&str1);
    clear_string(&str2);
    clear_string(&str3);
    printf("str1,str2,str3 have been cleared\n\n");
    // TASK 2
    printf("Mashrabova MP Lab 3 Task 4.2:\n\n");
    Post *post = NULL;
    size_t current_mail_count = 0; // количество изначально
    size_t max_mail_capacity = 2;  // (если добавим 3 - то удвоем размер)
    // вводим адрес1 + проверки на размер введенных значений и валидация
    printf("Enter post office address:\n");
    char city[INPUT];
    check_input("City (str): ", city, INPUT, 0);
    char street[INPUT];
    check_input("Street (str): ", street, INPUT, 0);
    char num_house[INPUT];
    check_input("House number (int): ", num_house, INPUT, 1);
    char building[INPUT];
    check_input("Building (str): ", building, INPUT, 0);
    char num_apart[INPUT];
    check_input("Apartament number (int): ", num_apart, INPUT, 1);
    char id_6[INPUT];
    check_input("Index (int, 6): ", id_6, INPUT, 2);
    // добавляем в структуру
    Address post_address;
    switch (create_address(&post_address, city, street, num_house, building, num_apart, id_6))
    {
    case correct_data:
        switch (create_post(&post, &post_address, &current_mail_count, &max_mail_capacity))
        {
        case correct_data:
            printf("Post office address ADDED\n\n");
            break;
        case memory_alloc_error:
            printf("Memory allocation error\n");
            return 1;
        default:
            printf("Incorrect data\n");
            return 1;
        }
        break;
    case memory_alloc_error:
        printf("Memory allocation error\n");
        return 1;
    default:
        printf("Incorrect data\n");
        return 1;
    }
    // меню действий
    while (1)
    {
        char act[INPUT];
        printf("Choose an action:\n");
        printf("<add>  - ADD a mail to the post office\n");
        printf("<delete> - DELETE a mail to the post office\n");
        printf("<search> - SEARCH by id Mail\n");
        printf("<sort> - SORT a mail to the post office\n");
        printf("<time> - SEARCH for mails where delivery time has expired\n");
        printf("<print> - printing of all delivered\n");
        printf("<exit> - exit\n\n");
        printf("ENTER ----> ");
        scanf("%s", act);

        if (strcmp(act, "add") == 0)
        {
            fgets(act, sizeof(act), stdin);
            printf("Enter address and information about Mail:\n");
            char city[INPUT];
            check_input("City (str): ", city, INPUT, 0);
            char street[INPUT];
            check_input("Street (str): ", street, INPUT, 0);
            char num_house[INPUT];
            check_input("House number (int): ", num_house, INPUT, 1);
            char building[INPUT];
            check_input("Building (str): ", building, INPUT, 0);
            char num_apart[INPUT];
            check_input("Apartament number (int): ", num_apart, INPUT, 1);
            char id_6[INPUT];
            check_input("Index (int, 6): ", id_6, INPUT, 2);
            Address mail_address;
            switch (create_address(&mail_address, city, street, num_house, building, num_apart, id_6))
            {
            case correct_data:
                char weight[INPUT];
                check_input("Weignt (double): ", weight, INPUT, 3);
                char id_14[INPUT];
                check_input("index mail (int, 14): ", id_14, INPUT, 4);
                char creation_time[INPUT];
                check_input("Creation time (dd:MM:yyyy hh:mm:ss): ", creation_time, INPUT, 5);
                char delivery_time[INPUT];
                check_input("Delivery time (dd:MM:yyyy hh:mm:ss): ", delivery_time, INPUT, 5);
                Mail mail;
                switch (create_mail(&mail, mail_address, weight, id_14, creation_time, delivery_time))
                {
                case correct_data:
                    switch (add_mail_in_post(&post, mail, &current_mail_count, &max_mail_capacity))
                    {
                    case correct_data:
                        printf("Mail information and address ADDED\n\n");
                        break;
                    case memory_alloc_error:
                        printf("Memory allocation error\n");
                        return 1;
                    default:
                        printf("Incorrect data-such mail already exists\n\n");
                        continue;
                    }
                    break;
                case memory_alloc_error:
                    printf("Memory allocation error\n");
                    return 1;
                default:
                    printf("Incorrect data\n");
                    continue;
                }
                break;
            case memory_alloc_error:
                printf("Memory allocation error\n");
                return 1;
            default:
                printf("Incorrect data\n");
                continue;
            }
        }

        else if (strcmp(act, "delete") == 0)
        {
            printf("\nEnter index msil ---> ");
            char id_14[INPUT];
            check_input("index mail (int, 14): ", id_14, INPUT, 4);
            String str_id_14;
            if (create_string(id_14, &str_id_14) == memory_alloc_error)
            {
                printf("Memory allocation error\n");
                return 1;
            }
            else
            {
                switch (mail_deleted(&post, str_id_14, current_mail_count))
                {
                case correct_data:
                    printf("Mail DELETED\n\n");
                    break;
                case memory_alloc_error:
                    printf("Memory allocation error\n");
                    return 1;
                default:
                    printf("Incorrect data-Mail doesn't exist \n\n");
                    continue;
                }
            }
        }

        else if (strcmp(act, "search") == 0)
        {
        }

        else if (strcmp(act, "sort") == 0)
        {
        }

        else if (strcmp(act, "time") == 0)
        {
        }

        else if (strcmp(act, "print") == 0)
        {
        }

        else if (strcmp(act, "exit") == 0)
        {
        }

        else
        {
            printf("There is no such action\n\n");
        }
    }

    return 0;
}
