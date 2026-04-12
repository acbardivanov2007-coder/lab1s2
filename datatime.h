#ifndef DATATIME_H
#define DATATIME_H

#include <stdio.h>
#include <stdlib.h>

// Описание структуры с использованием typedef
typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
} datatime;

// --- "Конструкторы" (возвращают указатель на выделенную память) ---
// Конструктор по умолчанию (установит базовую дату, например 01.01.1970)
datatime* datatime_create_default(void);

// Конструктор с параметрами
datatime* datatime_create(int year, int month, int day, int hour, int minute);

// Конструктор копирования
datatime* datatime_create_copy(const datatime* source);

// --- "Деструктор" ---
// Освобождает динамическую память
void datatime_destroy(datatime* dt);

// --- Методы варианта 3 ---
// Форматированный строковый ввод (создает объект из строки "YYYY-MM-DD HH:MM")
datatime* datatime_from_string(const char* str);

// Форматированный строковый вывод
void datatime_print(const datatime* dt);

// Нахождение временного интервала (dt2 - dt1)
void datatime_difference(const datatime* dt1, const datatime* dt2);

#endif // DATATIME_H
