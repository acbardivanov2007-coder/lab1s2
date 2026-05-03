#include <stdio.h>
#include <stdlib.h> // Тут живут malloc и free
#include "device.h"

// "Конструктор"
device* device_create(void) {
    // Просим у системы память под структуру device
    device* dev = (device*)malloc(sizeof(device));
    if (dev != NULL) { // Если память успешно выделена
        // Устанавливаем значения по умолчанию
        dev->display_type = 0;
        dev->brightness = 5;
        dev->time_format = 1; // 24h
        dev->alarm_flag = 0;
        dev->memory_size = 0; // 16KB
        dev->processor_type = 0;
        dev->water_resistance = 0;
    }
    return dev; // Возвращаем адрес выделенной памяти
}

// "Деструктор"
void device_destroy(device* dev) {
    if (dev != NULL) {
        free(dev); // Отдаем память обратно системе
    }
}

// Метод для заполнения структуры (setter)
void device_setup(device* dev, unsigned int disp, unsigned int bright, unsigned int fmt, 
                  unsigned int alarm, unsigned int mem, unsigned int proc, unsigned int water) {
    if (dev != NULL) {
        // Присваиваем значения полям. Важно передавать числа, которые поместятся в биты!
        dev->display_type = disp;
        dev->brightness = bright;
        dev->time_format = fmt;
        dev->alarm_flag = alarm;
        dev->memory_size = mem;
        dev->processor_type = proc;
        dev->water_resistance = water;
    }
}

// Метод для вывода информации об устройстве
void device_print(const device* dev) {
    if (dev != NULL) {
        printf("--- Данные устройства ---\n");
        printf("Тип дисплея: %u\n", dev->display_type);
        printf("Яркость: %u/15\n", dev->brightness);
        printf("Формат времени: %s\n", dev->time_format == 0 ? "12 часов" : "24 часа");
        printf("Будильник: %s\n", dev->alarm_flag ? "ВКЛЮЧЕН" : "ВЫКЛЮЧЕН");
        
        // Расшифровываем память
        int mem_kb = 16;
        if (dev->memory_size == 1) mem_kb = 32;
        if (dev->memory_size == 2) mem_kb = 64;
        if (dev->memory_size == 3) mem_kb = 128;
        printf("Объем памяти: %dKB\n", mem_kb);
        
        printf("Процессор: Тип %u\n", dev->processor_type);
        
        // Расшифровываем водозащиту
        const char* water_str = "Нет";
        if (dev->water_resistance == 1) water_str = "IP67";
        if (dev->water_resistance == 2) water_str = "IP68";
        printf("Водостойкость: %s\n", water_str);
        printf("-------------------------\n");
    }
}
