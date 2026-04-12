#include <stdio.h>
#include "datatime.h"

int main() {
    printf("=== Тестирование расширенного функционала ===\n\n");

    datatime* dt1 = datatime_create_default();
    datatime* dt2 = datatime_from_string("2023-12-31 23:59");
    
    printf("\n--- 1. Вывод отдельных полей ---\n");
    datatime_print_date(dt2);
    datatime_print_time(dt2);

    printf("\n--- 2. Сеттеры и изменение (++) ---\n");
    printf("Было: "); datatime_print(dt2);
    printf("Инкремент (++) на 1 минуту...\n");
    datatime_increment(dt2);
    printf("Стало: "); datatime_print(dt2); // Должен стать 2024-01-01 00:00

    printf("\n--- 3. Изменение (--) ---\n");
    datatime_decrement(dt2);
    printf("Декремент (--), вернулись: "); datatime_print(dt2);

    printf("\n--- 4. Сравнение (==, !=, >) ---\n");
    datatime_set_year(dt1, 2025);
    printf("dt1: "); datatime_print(dt1);
    printf("dt2: "); datatime_print(dt2);
    
    if (datatime_is_greater(dt1, dt2)) printf("dt1 БОЛЬШЕ dt2\n");
    if (datatime_is_not_equal(dt1, dt2)) printf("dt1 НЕ РАВНО dt2\n");

    printf("\n--- 5. Интервал ---\n");
    datatime_difference(dt2, dt1);

    printf("\n--- 6. Очистка ---\n");
    datatime_destroy(dt1);
    datatime_destroy(dt2);

    return 0;
}
