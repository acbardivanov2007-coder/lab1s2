#include <stdio.h>
#include <stdlib.h>
#include "device.h"

// 1. Конструктор: создает новое устройство в динамической памяти
device* device_create() {
    // Просим у кучи (heap) место размером с нашу структуру [cite: 129]
    device* dev = (device*)malloc(sizeof(device)); 
    
    if (dev != NULL) { // Всегда проверяем, выделилась ли память!
        // Инициализируем все побитовые поля нулями по умолчанию
        dev->display_type = 0;
        dev->brightness = 0;
        dev->time_format = 0;
        dev->alarm_flag = 0;
        dev->memory = 0;
        dev->cpu_type = 0;
        dev->water_resistance = 0;
    }
    return dev; // Возвращаем адрес созданного устройства
}

// 2. Деструктор: освобождает память, занятую устройством
void device_destroy(device* dev) {
    if (dev != NULL) {
        free(dev); // Отдаем память обратно операционной системе
    }
}

// 3. Функция вывода параметров устройства на экран
void device_print(const device* dev) {
    if (dev == NULL) return;
    // Печатаем все 7 параметров в одну строку для компактности
    printf("Дисплей: %u, Яркость: %u, Формат: %u, Будильник: %u, Память: %u, ЦП: %u, Водозащита: %u\n",
           dev->display_type, dev->brightness, dev->time_format, dev->alarm_flag,
           dev->memory, dev->cpu_type, dev->water_resistance);
}
