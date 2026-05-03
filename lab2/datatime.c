#include <stdio.h>
#include <stdlib.h>
#include "datatime.h"

// Конструктор по умолчанию
datatime* datatime_create(void) {
    datatime* dt = (datatime*)malloc(sizeof(datatime));
    if (dt != NULL) {
        dt->day = 1;
        dt->month = 1;
        dt->year = 2026;
        dt->hours = 12;
        dt->minutes = 0;
        
        // ВАЖНО: Вложенное выделение памяти! 
        // Создаем устройство и сохраняем адрес внутри dt
        dt->dev_info = device_create(); 
    }
    return dt;
}

// Деструктор
void datatime_destroy(datatime* dt) {
    if (dt != NULL) {
        // СНАЧАЛА освобождаем вложенную память устройства
        if (dt->dev_info != NULL) {
            device_destroy(dt->dev_info); 
        }
        // ПОТОМ освобождаем саму структуру даты
        free(dt);
    }
}

void datatime_print(const datatime* dt) {
    if (dt != NULL) {
        printf("Дата: %02d.%02d.%04d | Время: %02d:%02d\n", 
               dt->day, dt->month, dt->year, dt->hours, dt->minutes);
        
        // Печатаем данные вложенного устройства
        if (dt->dev_info != NULL) {
            device_print(dt->dev_info);
        }
    }
}
