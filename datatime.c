#include "datatime.h"
#include <string.h>
#include <ctype.h>

// Вспомогательная функция для расчета дней в месяце
static int days_in_month(int month, int year) {
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
        return 29;
    }
    return days[month - 1];
}

// --- БЕЗОПАСНЫЙ ВВОД (Защита от некорректных данных) ---
static int read_valid_int(const char* prompt, int min_val, int max_val) {
    char buffer[256];
    int value;
    char junk; // Для отлова лишних символов (например "12abc")

    while (true) {
        printf("%s", prompt);
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            clearerr(stdin);
            continue;
        }

        // Если sscanf успешно считал одно число и больше НИЧЕГО (junk не заполнен)
        if (sscanf(buffer, "%d %c", &value, &junk) == 1) {
            if (value >= min_val && value <= max_val) {
                return value; // Успех
            } else {
                printf("[ОШИБКА] Число должно быть в диапазоне от %d до %d.\n", min_val, max_val);
            }
        } else {
            printf("[ОШИБКА] Некорректный ввод. Пожалуйста, введите только целое число.\n");
        }
    }
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
        // Ставим базовые значения на случай, если передали мусор, затем используем сеттеры
        dt->year = 1970; dt->month = 1; dt->day = 1; dt->hour = 0; dt->minute = 0;
        datatime_set_year(dt, year);
        datatime_set_month(dt, month);
        datatime_set_day(dt, day);
        datatime_set_hour(dt, hour);
        datatime_set_minute(dt, minute);
        printf("[DEBUG] Конструктор С ПАРАМЕТРАМИ.\n");
    }
    return dt;
}

datatime* datatime_create_copy(const datatime* source) {
    if (!source) return NULL;
    return datatime_create(source->year, source->month, source->day, source->hour, source->minute);
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

// --- Вывод и Парсинг ---
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
        printf("--- Ввод даты и времени ---\n");
        dt->year = read_valid_int("Введите год (1-9999): ", 1, 9999);
        dt->month = read_valid_int("Введите месяц (1-12): ", 1, 12);
        
        int max_d = days_in_month(dt->month, dt->year);
        char day_prompt[100];
        sprintf(day_prompt, "Введите день (1-%d): ", max_d);
        dt->day = read_valid_int(day_prompt, 1, max_d);
        
        dt->hour = read_valid_int("Введите часы (0-23): ", 0, 23);
        dt->minute = read_valid_int("Введите минуты (0-59): ", 0, 59);
    }
}

void datatime_input_year(datatime* dt) {
    if (dt) dt->year = read_valid_int("Введите год (1-9999): ", 1, 9999);
}

void datatime_input_month(datatime* dt) {
    if (dt) {
        dt->month = read_valid_int("Введите месяц (1-12): ", 1, 12);
        // Корректируем день, если в новом месяце меньше дней (например, 31 января -> меняем на февраль -> станет 28)
        int max_d = days_in_month(dt->month, dt->year);
        if (dt->day > max_d) dt->day = max_d;
    }
}

void datatime_input_day(datatime* dt) {
    if (dt) {
        int max_d = days_in_month(dt->month, dt->year);
        char prompt[100];
        sprintf(prompt, "Введите день (1-%d): ", max_d);
        dt->day = read_valid_int(prompt, 1, max_d);
    }
}

// --- Изменение данных (Защищенные Сеттеры) ---
void datatime_set_year(datatime* dt, int year) {
    if (dt && year >= 1 && year <= 9999) dt->year = year;
}
void datatime_set_month(datatime* dt, int month) {
    if (dt && month >= 1 && month <= 12) dt->month = month;
}
void datatime_set_day(datatime* dt, int day) {
    if (dt && day >= 1 && day <= days_in_month(dt->month, dt->year)) dt->day = day;
}
void datatime_set_hour(datatime* dt, int hour) {
    if (dt && hour >= 0 && hour <= 23) dt->hour = hour;
}
void datatime_set_minute(datatime* dt, int minute) {
    if (dt && minute >= 0 && minute <= 59) dt->minute = minute;
}

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
