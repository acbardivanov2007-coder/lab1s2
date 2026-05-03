#include <stdio.h>
#include "datatime.h"

int main() {
    printf("--- Тестирование 'Конструкторов' ---\n");
    
    // 1. Создание по умолчанию
    datatime* dt1 = datatime_create_default();
    printf("dt1 (по умолчанию): ");
    datatime_print(dt1);

    // 2. Создание с параметрами (31 декабря 2023, 23:59)
    datatime* dt2 = datatime_create(31, 12, 2023, 23, 59);
    printf("dt2 (с параметрами): ");
    datatime_print(dt2);

    // 3. Создание копии
    datatime* dt3 = datatime_copy(dt2);
    printf("dt3 (копия dt2): ");
    datatime_print(dt3);

    printf("\n--- Тестирование Инкремента (++) и Декремента (--) ---\n");
    datatime_increment(dt2); // 23:59 -> 00:00 следующего дня/года
    printf("dt2 после ++ (переход года): ");
    datatime_print(dt2);

    datatime_decrement(dt3); // Отнимаем минуту от копии
    printf("dt3 после -- (минус минута): ");
    datatime_print(dt3);

    printf("\n--- Тестирование Сравнения ---\n");
    if (datatime_is_greater(dt2, dt3)) {
        printf("dt2 больше, чем dt3\n");
    }
    if (datatime_is_not_equal(dt1, dt2)) {
        printf("dt1 не равно dt2\n");
    }

    printf("\n--- Тестирование Сеттеров ---\n");
    datatime_set_year(dt1, 2025);
    datatime_set_hours(dt1, 15);
    printf("dt1 после изменения года и часов: ");
    datatime_print(dt1);

    // Тестирование ввода с клавиатуры (раскомментируй, если нужно ввести вручную)
    // datatime_input(dt1);
    // printf("Вы ввели: ");
    // datatime_print(dt1);

    printf("\n--- Вызов 'Деструкторов' (освобождение памяти) ---\n");
    // Если мы выделили память (malloc), мы ОБЯЗАНЫ её очистить (free)
    datatime_destroy(dt1);
    datatime_destroy(dt2);
    datatime_destroy(dt3);
    printf("Память успешно очищена!\n");

    return 0;
}
