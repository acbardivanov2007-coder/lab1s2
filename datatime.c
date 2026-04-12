#include "datatime.h"

// Вспомогательная функция для расчета дней в месяце (учитывает високосные года)
static int days_in_month(int month, int year) {
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            return 29;
        }
    }
    return days[month - 1];
}

datatime* datatime_create_default(void) {
    datatime* dt = (datatime*)malloc(sizeof(datatime));
    if (dt) {
        dt->year = 1970;
        dt->month = 1;
        dt->day = 1;
        dt->hour = 0;
        dt->minute = 0;
        printf("[DEBUG] Вызван конструктор ПО УМОЛЧАНИЮ.\n");
    }
    return dt;
}

datatime* datatime_create(int year, int month, int day, int hour, int minute) {
    datatime* dt = (datatime*)malloc(sizeof(datatime));
    if (dt) {
        dt->year = year;
        dt->month = month;
        dt->day = day;
        dt->hour = hour;
        dt->minute = minute;
        printf("[DEBUG] Вызван конструктор С ПАРАМЕТРАМИ.\n");
    }
    return dt;
}

datatime* datatime_create_copy(const datatime* source) {
    if (!source) return NULL;
    datatime* dt = (datatime*)malloc(sizeof(datatime));
    if (dt) {
        dt->year = source->year;
        dt->month = source->month;
        dt->day = source->day;
        dt->hour = source->hour;
        dt->minute = source->minute;
        printf("[DEBUG] Вызван конструктор КОПИРОВАНИЯ.\n");
    }
    return dt;
}

void datatime_destroy(datatime* dt) {
    if (dt) {
        free(dt);
        printf("[DEBUG] Вызван ДЕСТРУКТОР. Память освобождена.\n");
    }
}

datatime* datatime_from_string(const char* str) {
    int y, m, d, h, min;
    if (sscanf(str, "%d-%d-%d %d:%d", &y, &m, &d, &h, &min) == 5) {
        return datatime_create(y, m, d, h, min);
    }
    printf("Ошибка парсинга строки!\n");
    return NULL;
}

void datatime_print(const datatime* dt) {
    if (dt) {
        printf("%04d-%02d-%02d %02d:%02d\n", dt->year, dt->month, dt->day, dt->hour, dt->minute);
    }
}

void datatime_difference(const datatime* dt1, const datatime* dt2) {
    if (!dt1 || !dt2) return;

    // Считаем, что dt2 > dt1
    int dy = dt2->year - dt1->year;
    int dm = dt2->month - dt1->month;
    int dd = dt2->day - dt1->day;
    int dh = dt2->hour - dt1->hour;
    int dmin = dt2->minute - dt1->minute;

    // Классический алгоритм вычитания столбиком с заимствованием
    if (dmin < 0) {
        dmin += 60;
        dh--;
    }
    if (dh < 0) {
        dh += 24;
        dd--;
    }
    if (dd < 0) {
        int prev_month = dt2->month - 1;
        int prev_year = dt2->year;
        if (prev_month == 0) {
            prev_month = 12;
            prev_year--;
        }
        dd += days_in_month(prev_month, prev_year);
        dm--;
    }
    if (dm < 0) {
        dm += 12;
        dy--;
    }

    printf("Интервал: %d лет, %d месяцев, %d дней, %d часов, %d минут\n", 
           dy, dm, dd, dh, dmin);
}
