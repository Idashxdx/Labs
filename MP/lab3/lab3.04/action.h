
#ifndef action_h
#define action_h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define EPSILON 1e-9
#define INPUT 50
typedef enum check_data
{
    correct_data,
    incorrect_data,
    memory_alloc_error
} check_data;
//task1
typedef struct
{
    char *str;
    int length;
} String;
// task2
typedef struct
{
    String city;
    String street;
    int num_house;
    String building;
    int num_apart;
    int id_6;
} Address;
typedef struct
{
    Address address;
    double weight;
    String id_14;
    String creation_time;
    String delivery_time;
} Mail;
typedef struct
{
    Address *address;
    Mail *mail;
} Post;
//task1
check_data create_string(const char *input, String *str);
int equality(const String str1, const String str2);
check_data copy_string(String *new_str1, const String str2);
check_data copy_to_dinamic_string(const String str1, String *str2);
int compare_string(const String str1, const String str2);
check_data concatenation_string(String *new_str1, const String str2);
void clear_string(String *str);
//task2
int valid_num(const char *str);
int valid_id_6(const char *index);
int valid_id_14(const char *index);
int valid_weight(const char *weight);
int valid_datetime(const char *datetime);
void check_input(const char *print, char *input, int size, int valid);
check_data create_address(Address *address, char *city, char *street, char *num_house_str, char *building, char *num_apart_str, char *id_6_str);
check_data create_mail(Mail *mail, Address address, char* weight_str, char *id_14_str, char *creation_time, char* delivery_time);
void print_mail(Mail mail);
check_data search_mail(Post *post, String id_14, size_t count);
check_data create_post(Post** post, Mail mail, size_t *count, size_t *max_count);
#endif
