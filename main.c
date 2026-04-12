#include <stdio.h>
#include "datatime.h"

int main() {
    printf("========== ИТОГОВОЕ ТЕСТИРОВАНИЕ СТРУКТУРЫ DATATIME ==========\n\n");

    // 1. Создание
    printf("--- 1. Создание объектов ---\n");
    datatime* dt1 = datatime_create_default();
    datatime* dt2 = datatime_from_string("2023-12-31 23:59");
    datatime* dt_copy = datatime_create_copy(dt2);
    
    printf("dt1 (по умолчанию): "); datatime_print(dt1);
    printf("dt2 (из строки):    "); datatime_print(dt2);
    printf("dt_copy (копия dt2):"); datatime_print(dt_copy);

    // 2. Инкремент и Декремент
    printf("\n--- 2. Инкремент (++) и Декремент (--) ---\n");
    printf("До инкремента dt2:  "); datatime_print(dt2);
    datatime_increment(dt2);
    printf("После инкремента:   "); datatime_print(dt2); // Должен стать 2024-01-01 00:00
    
    datatime_decrement(dt2);
    printf("После декремента:   "); datatime_print(dt2); // Вернулись к 2023-12-31 23:59

    // 3. Ручной ввод и Сеттеры
    printf("\n--- 3. Ручной ввод и Сеттеры ---\n");
    datatime_set_year(dt1, 2025);
    printf("Изменили год dt1 (через setter): "); datatime_print(dt1);
    
    printf("\n[ТЕСТ ВВОДА] Давайте изменим месяц для dt1.\n");
    datatime_input_month(dt1);
    printf("Теперь dt1 выглядит так: "); datatime_print(dt1);

    // 4. Сравнение
    printf("\n--- 4. Сравнение ---\n");
    if (datatime_is_greater(dt1, dt2)) {
        printf("dt1 БОЛЬШЕ, чем dt2\n");
    } else {
        printf("dt1 МЕНЬШЕ или РАВНО dt2\n");
    }

    // 5. Интервалы
    printf("\n--- 5. Временные интервалы ---\n");
    printf("Разница между dt1 и dt2:\n");
    datatime_difference(dt1, dt2);

    // 6. Освобождение памяти
    printf("\n--- 6. Очистка динамической памяти ---\n");
    datatime_destroy(dt1);
    datatime_destroy(dt2);
    datatime_destroy(dt_copy);

    printf("\nПрограмма успешно завершена.\n");
    return 0;
}
