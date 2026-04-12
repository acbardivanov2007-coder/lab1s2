#include "bitstruct.h"
#include <stdio.h>
#include <stdlib.h>

// Конструктор устройства
device* device_create(datatime* dt) {
    device* dev = (device*)malloc(sizeof(device));
    if (dev) {
        dev->clock = dt; // Встраиваем зависимость
        
        // Значения по умолчанию
        dev->display_type = 0;
        dev->brightness = 5;
        dev->time_format = 1; // 24h
        dev->alarm_flag = 0;
        dev->memory_size = 0;
        dev->cpu_type = 0;
        dev->water_resist = 0;
        printf("[DEBUG] Устройство создано в дин. памяти.\n");
    }
    return dev;
}

// Деструктор устройства
void device_destroy(device* dev) {
    if (dev) {
        // Мы уничтожаем только само устройство. 
        // Время (clock) уничтожается отдельно, так как оно может использоваться где-то еще.
        free(dev);
        printf("[DEBUG] Память устройства освобождена.\n");
    }
}

// Методы заполнения с базовой защитой от переполнения
void device_set_display(device* dev, unsigned char type) {
    if (dev && type <= 2) dev->display_type = type;
}
void device_set_brightness(device* dev, unsigned char level) {
    if (dev && level <= 15) dev->brightness = level;
}
void device_set_time_format(device* dev, unsigned char format) {
    if (dev && format <= 1) dev->time_format = format;
}
void device_set_alarm(device* dev, unsigned char flag) {
    if (dev && flag <= 1) dev->alarm_flag = flag;
}
void device_set_memory(device* dev, unsigned char mem) {
    if (dev && mem <= 3) dev->memory_size = mem;
}
void device_set_cpu(device* dev, unsigned char cpu) {
    if (dev && cpu <= 2) dev->cpu_type = cpu;
}
void device_set_water_resist(device* dev, unsigned char wr) {
    if (dev && wr <= 2) dev->water_resist = wr;
}

// Красивый вывод статуса устройства
void device_print_info(const device* dev) {
    if (!dev) return;
    
    printf("\n=== ИНФОРМАЦИЯ ОБ УСТРОЙСТВЕ ===\n");
    printf("Дисплей:       %s\n", dev->display_type == 0 ? "LCD" : (dev->display_type == 1 ? "OLED" : "E-ink"));
    printf("Яркость:       %d/15\n", dev->brightness);
    printf("Формат:        %d-часовой\n", dev->time_format == 0 ? 12 : 24);
    printf("Будильник:     %s\n", dev->alarm_flag ? "ВКЛЮЧЕН" : "ВЫКЛЮЧЕН");
    
    const char* mem_str[] = {"16KB", "32KB", "64KB", "128KB"};
    printf("Память:        %s\n", mem_str[dev->memory_size]);
    
    const char* cpu_str[] = {"ARM", "RISC-V", "x86"};
    printf("Процессор:     %s\n", cpu_str[dev->cpu_type]);
    
    const char* wr_str[] = {"Нет", "IP67", "IP68"};
    printf("Влагозащита:   %s\n", wr_str[dev->water_resist]);
    
    printf("Текущее время: ");
    if (dev->clock) {
        datatime_print(dev->clock);
    } else {
        printf("не установлено\n");
    }
    printf("================================\n");
}
