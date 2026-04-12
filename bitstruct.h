#ifndef BITSTRUCT_H
#define BITSTRUCT_H

#include "datatime.h"

// --- НЕВЫРОВНЕННАЯ СТРУКТУРА (для демонстрации в отчете) ---
// Компилятор добавит padding (пустые байты) для выравнивания
typedef struct {
    datatime* clock;               // 8 байт (на 64-bit системах)
    unsigned int display_type : 2; // Базовый тип int (обычно 4 байта)
    unsigned int brightness   : 4; 
    unsigned int time_format  : 1; 
    unsigned int alarm_flag   : 1; 
    unsigned int memory_size  : 2; 
    unsigned int cpu_type     : 2; 
    unsigned int water_resist : 2; 
} device_unaligned;


// --- ВЫРОВНЕННАЯ (УПАКОВАННАЯ) СТРУКТУРА ---
// Заставляем компилятор паковать данные по 1 байту (без пустот)
#pragma pack(push, 1)
typedef struct {
    datatime* clock;                // Встроенная структура времени
    
    // Используем unsigned char (1 байт) для максимального уплотнения
    unsigned char display_type : 2; // 0: LCD, 1: OLED, 2: E-ink
    unsigned char brightness   : 4; // 0-15 уровней
    unsigned char time_format  : 1; // 0: 12h, 1: 24h
    unsigned char alarm_flag   : 1; // 0: Выкл, 1: Вкл
    // Итого: 8 бит = 1 байт заполнен полностью
    
    unsigned char memory_size  : 2; // 0: 16KB, 1: 32KB, 2: 64KB, 3: 128KB
    unsigned char cpu_type     : 2; // 0: ARM, 1: RISC-V, 2: x86
    unsigned char water_resist : 2; // 0: Нет, 1: IP67, 2: IP68
    // Итого: 6 бит (займет 1 байт)
} device;
#pragma pack(pop)

// --- Методы ---
// Конструктор и деструктор
device* device_create(datatime* dt);
void device_destroy(device* dev);

// Методы заполнения полей
void device_set_display(device* dev, unsigned char type);
void device_set_brightness(device* dev, unsigned char level);
void device_set_time_format(device* dev, unsigned char format);
void device_set_alarm(device* dev, unsigned char flag);
void device_set_memory(device* dev, unsigned char mem);
void device_set_cpu(device* dev, unsigned char cpu);
void device_set_water_resist(device* dev, unsigned char wr);

// Вывод на экран
void device_print_info(const device* dev);

#endif // BITSTRUCT_H
