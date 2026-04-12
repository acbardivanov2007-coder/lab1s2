#ifndef DATATIME_H
#define DATATIME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Описание структуры
typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
} datatime;

// --- Конструкторы и деструктор ---
datatime* datatime_create_default(void);
datatime* datatime_create(int year, int month, int day, int hour, int minute);
datatime* datatime_create_copy(const datatime* source);
void datatime_destroy(datatime* dt);

// --- Сравнение объектов (==, !=, >, <, >=, <=) ---
// Возвращает <0 если dt1 < dt2, 0 если равны, >0 если dt1 > dt2
int datatime_compare(const datatime* dt1, const datatime* dt2);
bool datatime_is_equal(const datatime* dt1, const datatime* dt2);       // ==
bool datatime_is_not_equal(const datatime* dt1, const datatime* dt2);   // !=
bool datatime_is_greater(const datatime* dt1, const datatime* dt2);     // >
bool datatime_is_less(const datatime* dt1, const datatime* dt2);        // <
bool datatime_is_greater_or_equal(const datatime* dt1, const datatime* dt2); // >=
bool datatime_is_less_or_equal(const datatime* dt1, const datatime* dt2);    // <=

// --- Ввод/Вывод ---
void datatime_print(const datatime* dt);
void datatime_print_date(const datatime* dt); // Вывод только даты
void datatime_print_time(const datatime* dt); // Вывод только времени
datatime* datatime_from_string(const char* str);

// --- Изменение данных (++, --, setters) ---
void datatime_increment(datatime* dt); // ++ (добавляет 1 минуту)
void datatime_decrement(datatime* dt); // -- (отнимает 1 минуту)

void datatime_set_year(datatime* dt, int year);
void datatime_set_month(datatime* dt, int month);
void datatime_set_day(datatime* dt, int day);
void datatime_set_hour(datatime* dt, int hour);
void datatime_set_minute(datatime* dt, int minute);

// --- Нахождение интервалов ---
void datatime_difference(const datatime* dt1, const datatime* dt2);

#endif // DATATIME_H
