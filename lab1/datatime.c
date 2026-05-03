#include <stdio.h>
#include <stdlib.h>
#include "datatime.h"

// Вспомогательная функция для определения количества дней в месяце (с учетом високосных лет)
static int days_in_month(int month, int year) {
    if (month == 2) {
        // Проверка на високосный год
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) return 29;
        return 28;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
    return 31;
}

// --- Реализация "Конструкторов" ---

datatime* datatime_create_default() {
    // Выделяем память в куче размером с одну структуру datatime
    datatime* dt = (datatime*)malloc(sizeof(datatime));
    if (dt != NULL) { // Если память успешно выделилась
        dt->day = 1;
        dt->month = 1;
        dt->year = 2000;
        dt->hours = 0;
        dt->minutes = 0;
    }
    return dt; // Возвращаем указатель на созданный объект
}

datatime* datatime_create(int d, int m, int y, int h, int min) {
    datatime* dt = (datatime*)malloc(sizeof(datatime));
    if (dt != NULL) {
        dt->day = d;
        dt->month = m;
        dt->year = y;
        dt->hours = h;
        dt->minutes = min;
    }
    return dt;
}

datatime* datatime_copy(const datatime* source) {
    if (source == NULL) return NULL; // Защита от пустых указателей
    datatime* dt = (datatime*)malloc(sizeof(datatime));
    if (dt != NULL) {
        // Копируем все поля из исходного объекта в новый
        dt->day = source->day;
        dt->month = source->month;
        dt->year = source->year;
        dt->hours = source->hours;
        dt->minutes = source->minutes;
    }
    return dt;
}

// --- Реализация "Деструктора" ---

void datatime_destroy(datatime* dt) {
    if (dt != NULL) {
        free(dt); // Освобождаем память, чтобы не было утечек
    }
}

// --- Вспомогательная функция для сравнения ---
// Возвращает 1 если dt1 > dt2, -1 если dt1 < dt2, и 0 если равны.
static int compare_dates(const datatime* dt1, const datatime* dt2) {
    if (dt1->year != dt2->year) return (dt1->year > dt2->year) ? 1 : -1;
    if (dt1->month != dt2->month) return (dt1->month > dt2->month) ? 1 : -1;
    if (dt1->day != dt2->day) return (dt1->day > dt2->day) ? 1 : -1;
    if (dt1->hours != dt2->hours) return (dt1->hours > dt2->hours) ? 1 : -1;
    if (dt1->minutes != dt2->minutes) return (dt1->minutes > dt2->minutes) ? 1 : -1;
    return 0; // Все поля равны
}

// --- Реализация методов сравнения ---

int datatime_is_equal(const datatime* dt1, const datatime* dt2) {
    return compare_dates(dt1, dt2) == 0;
}

int datatime_is_not_equal(const datatime* dt1, const datatime* dt2) {
    return compare_dates(dt1, dt2) != 0;
}

int datatime_is_greater(const datatime* dt1, const datatime* dt2) {
    return compare_dates(dt1, dt2) == 1;
}

int datatime_is_less(const datatime* dt1, const datatime* dt2) {
    return compare_dates(dt1, dt2) == -1;
}

int datatime_is_greater_eq(const datatime* dt1, const datatime* dt2) {
    return compare_dates(dt1, dt2) >= 0;
}

int datatime_is_less_eq(const datatime* dt1, const datatime* dt2) {
    return compare_dates(dt1, dt2) <= 0;
}

// --- Ввод и Вывод ---

void datatime_print(const datatime* dt) {
    if (dt == NULL) return;
    // Форматированный вывод: %02d добавляет ведущий ноль (например, 05 вместо 5)
    printf("%02d.%02d.%04d %02d:%02d\n", dt->day, dt->month, dt->year, dt->hours, dt->minutes);
}

void datatime_input(datatime* dt) {
    if (dt == NULL) return;
    printf("Введите дату и время (ДД ММ ГГГГ ЧЧ ММ): ");
    scanf("%d %d %d %d %d", &dt->day, &dt->month, &dt->year, &dt->hours, &dt->minutes);
}

// --- Изменение данных (++ и --) ---

void datatime_increment(datatime* dt) {
    if (dt == NULL) return;
    dt->minutes++; // Добавляем минуту
    if (dt->minutes >= 60) {
        dt->minutes = 0;
        dt->hours++;
        if (dt->hours >= 24) {
            dt->hours = 0;
            dt->day++;
            if (dt->day > days_in_month(dt->month, dt->year)) {
                dt->day = 1;
                dt->month++;
                if (dt->month > 12) {
                    dt->month = 1;
                    dt->year++;
                }
            }
        }
    }
}

void datatime_decrement(datatime* dt) {
    if (dt == NULL) return;
    dt->minutes--; // Отнимаем минуту
    if (dt->minutes < 0) {
        dt->minutes = 59;
        dt->hours--;
        if (dt->hours < 0) {
            dt->hours = 23;
            dt->day--;
            if (dt->day < 1) {
                dt->month--;
                if (dt->month < 1) {
                    dt->month = 12;
                    dt->year--;
                }
                dt->day = days_in_month(dt->month, dt->year);
            }
        }
    }
}

// --- Setters (Сеттеры) ---

void datatime_set_day(datatime* dt, int d) { if (dt) dt->day = d; }
void datatime_set_month(datatime* dt, int m) { if (dt) dt->month = m; }
void datatime_set_year(datatime* dt, int y) { if (dt) dt->year = y; }
void datatime_set_hours(datatime* dt, int h) { if (dt) dt->hours = h; }
void datatime_set_minutes(datatime* dt, int min) { if (dt) dt->minutes = min; }
