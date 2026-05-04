#ifndef DEVICE_H
#define DEVICE_H
#include <stdlib.h>

// Структура устройства с побитовыми полями
typedef struct device {
    unsigned int display_type : 2;     // 0-3
    unsigned int brightness : 4;       // Уровни яркости 0-15
    unsigned int time_format : 1;      // 0 (12h) или 1 (24h)
    unsigned int alarm_flag : 1;       // 0 или 1
    unsigned int memory_size : 2;      // 0-3 (16KB, 32KB, 64KB, 128KB)
    unsigned int processor_type : 2;   // 0-3
    unsigned int water_resistance : 2; // 0 (Нет), 1 (IP67), 2 (IP68)
} device;

// Конструктор для создания устройства в динамической памяти
static inline device* device_create(unsigned int disp, unsigned int bright, unsigned int format, 
                                    unsigned int alarm, unsigned int mem, unsigned int proc, unsigned int water) {
    device* dev = (device*)malloc(sizeof(device));
    if (dev) {
        dev->display_type = disp;
        dev->brightness = bright;
        dev->time_format = format;
        dev->alarm_flag = alarm;
        dev->memory_size = mem;
        dev->processor_type = proc;
        dev->water_resistance = water;
    }
    return dev;
}

// Деструктор устройства
static inline void device_destroy(device* dev) {
    free(dev);
}

#endif
