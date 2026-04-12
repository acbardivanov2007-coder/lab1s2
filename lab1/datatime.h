// Эти две строчки (и #endif в самом конце) — это защита от повторного включения.
// Они гарантируют, что если этот файл случайно подключить дважды, программа не выдаст ошибку.
#ifndef DATATIME_H
#define DATATIME_H

// Подключаем базовые библиотеки языка Си.
#include <stdio.h>  // Нужна для работы функций ввода и вывода (например, printf)
#include <stdlib.h> // Нужна для выделения и освобождения памяти (malloc, free)

// Создаем наш собственный тип данных (структуру) с именем 'datatime'
typedef struct {
    int day;    // Переменная для хранения дня
    int month;  // Переменная для хранения месяца
    int year;   // Переменная для хранения года
    int hour;   // Переменная для хранения часов
    int minute; // Переменная для хранения минут
} datatime;

// Ниже идет список (прототипы) всех функций, которые мы реализуем в файле datatime.c.
// Это нужно, чтобы функция main знала, как к ним обращаться.

// Функции создания и удаления
datatime* datatime_create(int d, int m, int y, int h, int min); // Создает объект с конкретной датой
datatime* create_empty_datatime(); // Создает объект с "нулевой" датой
void datatime_destroy(datatime **dt); // Удаляет объект и освобождает память
void copy_datatime(datatime *dest, const datatime *src); // Копирует данные из одной даты в другую

// Функции вывода и сравнения
void datatime_print(const datatime *dt); // Печатает дату на экран
int datatime_compare(const datatime *dt1, const datatime *dt2); // Сравнивает, какая дата больше

// Функции увеличения времени (инкремент)
void datatime_min_increment(datatime *dt);   // Прибавляет 1 минуту
void datatime_hour_increment(datatime *dt);  // Прибавляет 1 час
void datatime_day_increment(datatime *dt);   // Прибавляет 1 день
void datatime_month_increment(datatime *dt); // Прибавляет 1 месяц

// Функции прямой установки значений (сеттеры)
void datatime_year_set(datatime *dt, int y);
void datatime_month_set(datatime *dt, int m);
void datatime_day_set(datatime *dt, int d);
void datatime_hour_set(datatime *dt, int h);
void datatime_min_set(datatime *dt, int min);

// Функции уменьшения времени (декремент)
void datatime_min_decrement(datatime *dt);   // Отнимает 1 минуту
void datatime_hour_decrement(datatime *dt);  // Отнимает 1 час
void datatime_day_decrement(datatime *dt);   // Отнимает 1 день
void datatime_month_decrement(datatime *dt); // Отнимает 1 месяц
void datatime_year_decrement(datatime *dt);  // Отнимает 1 год

// Функции для работы со строками (текстом)
char* datatime_to_string(const datatime *dt); // Превращает структуру в текст "ДД/ММ/ГГГГ ЧЧ:ММ"
datatime* datatime_from_string(const char *str); // Создает структуру, читая данные из текста

// Функции расчета разницы
void datatime_print_diff(const datatime *dt1, const datatime *dt2); // Печатает разницу в годах, месяцах и т.д.
unsigned long long datatime_to_minutes(const datatime *dt); // Переводит всю дату в суммарное количество минут от начала нашей эры
datatime* datatime_from_minutes(unsigned long long total_minutes); // Обратный процесс (из минут в дату)

#endif // Завершение защиты от повторного включения (DATATIME_H)
