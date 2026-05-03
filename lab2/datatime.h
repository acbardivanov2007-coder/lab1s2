#ifndef DATATIME_H
#define DATATIME_H

#include "device.h" // Подключаем файл со структурой устройства

typedef struct datatime {
    int day;
    int month;
    int year;
    int hours;
    int minutes;
    
    // ВСТРАИВАЕМ СТРУКТУРУ. Это указатель на структуру устройства.
    device* dev_info; 
} datatime;

datatime* datatime_create(void);
void datatime_destroy(datatime* dt);
void datatime_print(const datatime* dt);

#endif
