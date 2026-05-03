#ifndef DATATIME_H
#define DATATIME_H

// Объявляем структуру datatime с помощью typedef. 
// Теперь мы можем писать просто datatime вместо struct datatime.
typedef struct datatime {
    int day;
    int month;
    int year;
    int hours;
    int minutes;
} datatime;

// --- "Конструкторы" (Функции создания) ---
// Выделяют динамическую память и возвращают указатель на структуру
datatime* datatime_create_default(); // "По умолчанию" (создаст 01.01.2000 00:00)
datatime* datatime_create(int d, int m, int y, int h, int min); // С заданными параметрами
datatime* datatime_copy(const datatime* source); // Конструктор "копирования"

// --- "Деструктор" ---
// Освобождает динамическую память
void datatime_destroy(datatime* dt);

// --- Сравнение объектов ---
// Так как в C нельзя перегрузить ==, < и т.д., делаем это через функции.
// Возвращают 1 (true) или 0 (false)
int datatime_is_equal(const datatime* dt1, const datatime* dt2);      // ==
int datatime_is_not_equal(const datatime* dt1, const datatime* dt2);  // !=
int datatime_is_greater(const datatime* dt1, const datatime* dt2);    // >
int datatime_is_less(const datatime* dt1, const datatime* dt2);       // <
int datatime_is_greater_eq(const datatime* dt1, const datatime* dt2); // >=
int datatime_is_less_eq(const datatime* dt1, const datatime* dt2);    // <=

// --- Ввод / Вывод ---
void datatime_print(const datatime* dt);
void datatime_input(datatime* dt);

// --- Изменение данных ---
void datatime_increment(datatime* dt); // Аналог ++ (добавляем 1 минуту)
void datatime_decrement(datatime* dt); // Аналог -- (отнимаем 1 минуту)

// Сеттеры (Setter's) - функции для изменения отдельных полей
void datatime_set_day(datatime* dt, int d);
void datatime_set_month(datatime* dt, int m);
void datatime_set_year(datatime* dt, int y);
void datatime_set_hours(datatime* dt, int h);
void datatime_set_minutes(datatime* dt, int min);

#endif // DATATIME_H
