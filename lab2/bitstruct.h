// Эти две строчки защищают файл от повторного подключения. 
// Если файл уже был подключен ранее, компьютер просто пропустит его.
#ifndef BITSTRUCT_H
#define BITSTRUCT_H

// Подключаем стандартные библиотеки языка Си
#include <stdint.h> // Позволяет использовать типы данных с точным размером (например, uint16_t - ровно 16 бит)
#include <stdio.h>  // Нужна для ввода и вывода текста на экран (printf, scanf)
#include <stdlib.h> // Нужна для работы с памятью (выделение и очистка)

/* Здесь описано Задание на 3: Использование структуры с побитовыми полями.
Мы не тратим целые байты на каждое значение, а откусываем ровно столько битов, сколько нужно:
Б 0–2 - дисплей (от 0 до 3) - нужно 3 бита
Б 3–6 - яркость (от 0 до 15) - нужно 4 бита
и так далее...
*/

// Задание на 4: Использование функций выравнивания
// #pragma pack(push, 1) заставляет компьютер упаковывать данные максимально плотно,
// выравнивая их по границе 1 байта, чтобы не было пустых "дырок" в памяти.
#pragma pack(push, 1) 

// Создаем новую структуру (набор данных), где каждое поле занимает строго определенное число бит
typedef struct {
    uint16_t display      : 3; // Под дисплей выделяем 3 бита (может хранить числа от 0 до 7)
    uint16_t brightness   : 4; // Под яркость выделяем 4 бита (может хранить числа от 0 до 15)
    uint16_t time_format  : 1; // Формат времени 12/24 — достаточно 1 бита (0 или 1)
    uint16_t alarm        : 1; // Будильник вкл/выкл — тоже 1 бит
    uint16_t memory       : 2; // Память (4 варианта) — нужно 2 бита (от 0 до 3)
    uint16_t cpu          : 3; // Процессор (4 варианта) — хватило бы 2 бит, но по заданию выделяем 3
    uint16_t water        : 2; // Водостойкость (3 варианта) — нужно 2 бита
} device_data; // Называем этот набор "device_data"

// Возвращаем стандартные правила выравнивания памяти компьютера
#pragma pack(pop) 

// Создаем главную структуру для нашего устройства
typedef struct { 
    device_data data; // Внутри она содержит нашу плотно упакованную структуру с битами
} device;

// Ниже идет список функций (их "заголовки"). 
// Это нужно, чтобы другие файлы (например, main.c) знали, что такие функции существуют.
// Функции записи параметров (сеттеры):
void dev_set_display(device* d, uint16_t val); 
void dev_set_brightness(device* d, uint16_t value);
void dev_set_time_format(device* d, uint16_t value);
void dev_set_alarm(device* d, uint16_t value);
void dev_set_memory(device* d, uint16_t value);
void dev_set_cpu(device* d, uint16_t value);
void dev_set_water(device* d, uint16_t value);

// Функции чтения параметров (геттеры):
uint16_t dev_get_display(device* d);
uint16_t dev_get_brightness(device* d);
uint16_t dev_get_time_format(device* d);
uint16_t dev_get_alarm(device* d);
uint16_t dev_get_memory(device* d);
uint16_t dev_get_cpu(device* d);
uint16_t dev_get_water(device* d);

// Функции для создания и удаления устройства:
void dev_destroy(device* d); // Уничтожает устройство (очищает память)
device* dev_create(void);    // Создает новое устройство (выделяет память)

// Функция для безопасного ввода чисел от пользователя
int get_choice(uint16_t min, uint16_t max);

// Ключевое слово extern говорит, что эти списки цен и названий
// реально созданы в другом файле (в bitstruct.c), но мы хотим использовать их везде.
extern const int display_price[];
extern const int cpu_price[];
extern const int memory_price[];
extern const int water_price[];

extern const char* display_names[]; 
extern const char* cpu_names[];
extern const char* memory_names[];
extern const char* water_names[];

#endif /* BITSTRUCT_H */ // Конец защиты от повторного подключения
