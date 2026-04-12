#include <stdio.h>
#include "datatime.h"

int main() {
    printf("=== Демонстрация работы структуры datatime ===\n\n");

    printf("1. Проверка конструктора по умолчанию:\n");
    datatime* dt1 = datatime_create_default();
    printf("dt1: ");
    datatime_print(dt1);
    printf("\n");

    printf("2. Проверка конструктора с параметрами:\n");
    datatime* dt2 = datatime_create(2026, 4, 12, 18, 45);
    printf("dt2: ");
    datatime_print(dt2);
    printf("\n");

    printf("3. Проверка конструктора копирования (копия dt2):\n");
    datatime* dt3 = datatime_create_copy(dt2);
    printf("dt3: ");
    datatime_print(dt3);
    printf("\n");

    printf("4. Проверка строкового ввода (Парсинг):\n");
    const char* str = "2023-01-05 10:15";
    printf("Строка для парсинга: '%s'\n", str);
    datatime* dt4 = datatime_from_string(str);
    printf("dt4: ");
    datatime_print(dt4);
    printf("\n");

    printf("5. Нахождение временного интервала:\n");
    printf("От: "); datatime_print(dt4);
    printf("До: "); datatime_print(dt2);
    datatime_difference(dt4, dt2);
    printf("\n");

    printf("6. Очистка динамической памяти:\n");
    datatime_destroy(dt1);
    datatime_destroy(dt2);
    datatime_destroy(dt3);
    datatime_destroy(dt4);

    return 0;
}
