#include <stdio.h>
#include "datatime.h"

int main() {
    printf("Старт программы.\n\n");

    // 1. Создаем объект (память выделяется и для datatime, и для device внутри него)
    datatime* my_watch = datatime_create();
    if (my_watch == NULL) {
        printf("Ошибка выделения памяти!\n");
        return 1;
    }

    // 2. Печатаем значения по умолчанию
    printf("--- Изначальные настройки ---\n");
    datatime_print(my_watch);

    // 3. Изменяем время
    my_watch->hours = 8;
    my_watch->minutes = 30;

    // 4. Настраиваем устройство (используем setter)
    // disp=1, bright=10, fmt=0(12h), alarm=1(Вкл), mem=3(128KB), proc=2, water=2(IP68)
    device_setup(my_watch->dev_info, 1, 10, 0, 1, 3, 2, 2);

    // 5. Печатаем новые значения
    printf("\n--- После настройки ---\n");
    datatime_print(my_watch);

    // 6. Освобождаем память (вложенное удаление сработает автоматически внутри)
    datatime_destroy(my_watch);

    printf("\nПамять очищена. Конец программы.\n");
    return 0;
}
