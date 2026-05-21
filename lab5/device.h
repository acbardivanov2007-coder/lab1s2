#ifndef DEVICE_H
#define DEVICE_H

// Структура устройства с побитовыми полями для экономии памяти
typedef struct {
    unsigned int display_type : 2;     // 0-3
    unsigned int brightness : 4;       // 0-15
    unsigned int time_format : 1;      // 0 (12h) или 1 (24h)
    unsigned int alarm_flag : 1;       // 0 или 1
    unsigned int memory : 2;           // 0-3 (16, 32, 64, 128)
    unsigned int cpu_type : 2;         // 0-3
    unsigned int water_resistance : 2; // 0-2
} device;

// Конструктор и деструктор устройства
device* device_create();
void device_destroy(device* dev);
void device_print(const device* dev);

#endif
