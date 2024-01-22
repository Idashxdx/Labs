#include "action.h"

int main(int argc, char *argv[])
{

    // TASK 1
    // план: создаем какую нибудь строку и создаем то что добавим(функции). Соединяем(функция). Выводим, чистим память (функция).
    check_data status1;
    // 1. создания экземпляра типа String
    String str1 = create_string("qwerty ", &status1);
    switch (status1)
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
    check_data status2;
    String str2 = create_string("ytrewq", &status2);
    switch (status2)
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
    check_data status3;
    copy_string(&str1, str2, &status3);
    switch (status3)
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
    check_data status4;
    String str3 = copy_to_dinamic_string(str1, &status4);
    switch (status4)
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
    check_data status5;
    concatenation_string(&str1, str2, &status5);
    switch (status5)
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
    printf("M8O-211B-22  Mashrabova  lab3 tack4\n");
    return 0;
}
