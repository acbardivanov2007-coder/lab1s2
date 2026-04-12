#include "datatime.h"

// Вспомогательная функция для расчета дней в месяце
static int days_in_month(int month, int year) {
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
        return 29;
    }
    return days[month - 1];
}

// --- Конструкторы и Деструктор ---
datatime* datatime_create_default(void) {
    datatime* dt = (datatime*)malloc(sizeof(datatime));
    if (dt) {
        dt->year = 1970; dt->month = 1; dt->day = 1; dt->hour = 0; dt->minute = 0;
        printf("[DEBUG] Конструктор ПО УМОЛЧАНИЮ.\n");
    }
    return dt;
}

datatime* datatime_create(int year, int month, int day, int hour, int minute) {
    datatime* dt = (datatime*)malloc(sizeof(datatime));
    if (dt) {
        dt->year = year; dt->month = month; dt->day = day; dt->hour = hour; dt->minute = minute;
        printf("[DEBUG] Конструктор С ПАРАМЕТРАМИ.\n");
    }
    return dt;
}

datatime* datatime_create_copy(const datatime* source) {
    if (!source) return NULL;
    datatime* dt = (datatime*)malloc(sizeof(datatime));
    if (dt) {
        dt->year = source->year; dt->month = source->month; dt->day = source->day;
        dt->hour = source->hour; dt->minute = source->minute;
        printf("[DEBUG] Конструктор КОПИРОВАНИЯ.\n");
    }
    return dt;
}

void datatime_destroy(datatime* dt) {
    if (dt) {
        free(dt);
        printf("[DEBUG] Деструктор: память освобождена.\n");
    }
}

// --- Сравнение ---
int datatime_compare(const datatime* dt1, const datatime* dt2) {
    if (dt1->year != dt2->year) return dt1->year - dt2->year;
    if (dt1->month != dt2->month) return dt1->month - dt2->month;
    if (dt1->day != dt2->day) return dt1->day - dt2->day;
    if (dt1->hour != dt2->hour) return dt1->hour - dt2->hour;
    return dt1->minute - dt2->minute;
}

bool datatime_is_equal(const datatime* dt1, const datatime* dt2) { return datatime_compare(dt1, dt2) == 0; }
bool datatime_is_not_equal(const datatime* dt1, const datatime* dt2) { return datatime_compare(dt1, dt2) != 0; }
bool datatime_is_greater(const datatime* dt1, const datatime* dt2) { return datatime_compare(dt1, dt2) > 0; }
bool datatime_is_less(const datatime* dt1, const datatime* dt2) { return datatime_compare(dt1, dt2) < 0; }
bool datatime_is_greater_or_equal(const datatime* dt1, const datatime* dt2) { return datatime_compare(dt1, dt2) >= 0; }
bool datatime_is_less_or_equal(const datatime* dt1, const datatime* dt2) { return datatime_compare(dt1, dt2) <= 0; }

// --- Форматированный ввод/вывод (строки) ---
void datatime_print(const datatime* dt) {
    if (dt) printf("%04d-%02d-%02d %02d:%02d\n", dt->year, dt->month, dt->day, dt->hour, dt->minute);
}

void datatime_print_date(const datatime* dt) {
    if (dt) printf("Дата: %04d-%02d-%02d\n", dt->year, dt->month, dt->day);
}

void datatime_print_time(const datatime* dt) {
    if (dt) printf("Время: %02d:%02d\n", dt->hour, dt->minute);
}

datatime* datatime_from_string(const char* str) {
    int y, m, d, h, min;
    if (sscanf(str, "%d-%d-%d %d:%d", &y, &m, &d, &h, &min) == 5) {
        return datatime_create(y, m, d, h, min);
    }
    return NULL;
}

// --- Ручной ввод с клавиатуры ---
void datatime_input(datatime* dt) {
    if (dt) {
        printf("Введите дату и время (ГГГГ ММ ДД ЧЧ ММ): ");
        scanf("%d %d %d %d %d", &dt->year, &dt->month, &dt->day, &dt->hour, &dt->minute);
    }
}

void datatime_input_year(datatime* dt) {
    if (dt) {
        printf("Введите год: ");
        scanf("%d", &dt->year);
    }
}

void datatime_input_month(datatime* dt) {
    if (dt) {
        printf("Введите месяц (1-12): ");
        scanf("%d", &dt->month);
    }
}

void datatime_input_day(datatime* dt) {
    if (dt) {
        printf("Введите день: ");
        scanf("%d", &dt->day);
    }
}

// --- Изменение данных (Сеттеры) ---
void datatime_set_year(datatime* dt, int year) { if (dt) dt->year = year; }
void datatime_set_month(datatime* dt, int month) { if (dt) dt->month = month; }
void datatime_set_day(datatime* dt, int day) { if (dt) dt->day = day; }
void datatime_set_hour(datatime* dt, int hour) { if (dt) dt->hour = hour; }
void datatime_set_minute(datatime* dt, int minute) { if (dt) dt->minute = minute; }

// --- Инкремент (++) ---
void datatime_increment(datatime* dt) {
    if (!dt) return;
    dt->minute++;
    if (dt->minute >= 60) {
        dt->minute = 0; dt->hour++;
        if (dt->hour >= 24) {
            dt->hour = 0; dt->day++;
            if (dt->day > days_in_month(dt->month, dt->year)) {
                dt->day = 1; dt->month++;
                if (dt->month > 12) {
                    dt->month = 1; dt->year++;
                }
            }
        }
    }
}

// --- Декремент (--) ---
void datatime_decrement(datatime* dt) {
    if (!dt) return;
    dt->minute--;
    if (dt->minute < 0) {
        dt->minute = 59; dt->hour--;
        if (dt->hour < 0) {
            dt->hour = 23; dt->day--;
            if (dt->day < 1) {
                dt->month--;
                if (dt->month < 1) {
                    dt->month = 12; dt->year--;
                }
                dt->day = days_in_month(dt->month, dt->year);
            }
        }
    }
}

// --- Интервал ---
void datatime_difference(const datatime* dt1, const datatime* dt2) {
    if (!dt1 || !dt2) return;
    
    // Для простоты алгоритма предполагаем, что dt2 >= dt1
    const datatime* start = datatime_is_less(dt1, dt2) ? dt1 : dt2;
    const datatime* end = datatime_is_less(dt1, dt2) ? dt2 : dt1;

    int dy = end->year - start->year;
    int dm = end->month - start->month;
    int dd = end->day - start->day;
    int dh = end->hour - start->hour;
    int dmin = end->minute - start->minute;

    if (dmin < 0) { dmin += 60; dh--; }
    if (dh < 0) { dh += 24; dd--; }
    if (dd < 0) {
        int pm = end->month - 1, py = end->year;
        if (pm == 0) { pm = 12; py--; }
        dd += days_in_month(pm, py); dm--;
    }
    if (dm < 0) { dm += 12; dy--; }

    printf("Временной интервал: %d лет, %d мес, %d дней, %d ч, %d мин\n", dy, dm, dd, dh, dmin);
}
