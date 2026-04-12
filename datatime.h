#ifndef DATATIME_H
#define DATATIME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Описание структуры с использованием typedef
typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
} datatime;

// --- Конструкторы и Деструктор ---
datatime* datatime_create_default(void);
datatime* datatime_create(int year, int month, int day, int hour, int minute);
datatime* datatime_create_copy(const datatime* source);
void datatime_destroy(datatime* dt);

// --- Сравнение объектов (==, !=, >, <, >=, <=) ---
int datatime_compare(const datatime* dt1, const datatime* dt2);
bool datatime_is_equal(const datatime* dt1, const datatime* dt2);
bool datatime_is_not_equal(const datatime* dt1, const datatime* dt2);
bool datatime_is_greater(const datatime* dt1, const datatime* dt2);
bool datatime_is_less(const datatime* dt1, const datatime* dt2);
bool datatime_is_greater_or_equal(const datatime* dt1, const datatime* dt2);
bool datatime_is_less_or_equal(const datatime* dt1, const datatime* dt2);

// --- Форматированный ввод/вывод (строки) ---
void datatime_print(const datatime* dt);
void datatime_print_date(const datatime* dt);
void datatime_print_time(const datatime* dt);
datatime* datatime_from_string(const char* str);

// --- Ручной ввод с клавиатуры ---
void datatime_input(datatime* dt);
void datatime_input_year(datatime* dt);
void datatime_input_month(datatime* dt);
void datatime_input_day(datatime* dt);

// --- Изменение данных (++, --, setters) ---
void datatime_increment(datatime* dt); 
void datatime_decrement(datatime* dt); 

void datatime_set_year(datatime* dt, int year);
void datatime_set_month(datatime* dt, int month);
void datatime_set_day(datatime* dt, int day);
void datatime_set_hour(datatime* dt, int hour);
void datatime_set_minute(datatime* dt, int minute);

// --- Нахождение временных интервалов ---
void datatime_difference(const datatime* dt1, const datatime* dt2);

#endif // DATATIME_H
