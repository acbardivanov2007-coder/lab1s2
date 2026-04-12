#ifndef BITSTRUCT_H
#define BITSTRUCT_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Задание на 3: Использование структуры с побитовыми полями
Б 0–2 - display "3 - LCD, 4 - LED, 5 - OLED, 6 - E-Ink" 3 бита
Б 3–6 - brightness - от 0 до 15 4 бита
Б 7 - time format - "12h, 24h" 1 бит
Б 8 - alarm - "вкл, выкл" 1 бит
Б 9–10 - memory "16KB, 32KB, 64KB, 128KB" 2 бита
Б 11–13 - cpu "ARM, AVR, M-16pro, x86" 3 бита
Б 14–15 - water "Нет, IP67, IP68" 2 бита
*/

// Задание на 4: Использование функций выравнивания
#pragma pack(push, 1) // Устанавливаем выравнивание по границе 1 байта
typedef struct {
    uint16_t display      : 3; 
    uint16_t brightness   : 4; 
    uint16_t time_format  : 1; 
    uint16_t alarm        : 1; 
    uint16_t memory       : 2; 
    uint16_t cpu          : 3; 
    uint16_t water        : 2; 
} device_data;
#pragma pack(pop) // Возвращаем стандартное выравнивание

typedef struct { 
    device_data data; // Теперь используем структуру побитовых полей вместо uint16_t
} device;

void dev_set_display(device* d, uint16_t val);
void dev_set_brightness(device* d, uint16_t value);
void dev_set_time_format(device* d, uint16_t value);
void dev_set_alarm(device* d, uint16_t value);
void dev_set_memory(device* d, uint16_t value);
void dev_set_cpu(device* d, uint16_t value);
void dev_set_water(device* d, uint16_t value);

uint16_t dev_get_display(device* d);
uint16_t dev_get_brightness(device* d);
uint16_t dev_get_time_format(device* d);
uint16_t dev_get_alarm(device* d);
uint16_t dev_get_memory(device* d);
uint16_t dev_get_cpu(device* d);
uint16_t dev_get_water(device* d);

void dev_destroy(device* d);
device* dev_create(void);

int get_choice(uint16_t min, uint16_t max);

extern const int display_price[];
extern const int cpu_price[];
extern const int memory_price[];
extern const int water_price[];

extern const char* display_names[]; 
extern const char* cpu_names[];
extern const char* memory_names[];
extern const char* water_names[];

#endif /* BITSTRUCT_H */
