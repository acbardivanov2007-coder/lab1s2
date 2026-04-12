#include <stdio.h>
#include "datatime.h"
#include "bitstruct.h"

int main() {
    printf("========== ДЕМОНСТРАЦИЯ ПОБИТОВЫХ ПОЛЕЙ И ВЫРАВНИВАНИЯ ==========\n\n");

    // 1. Демонстрация для отчета
    printf("--- 1. Разница выравнивания в памяти ---\n");
    printf("Размер НЕВЫРОВНЕННОЙ структуры (device_unaligned): %zu байт\n", sizeof(device_unaligned));
    printf("Размер УПАКОВАННОЙ структуры   (device):           %zu байт\n", sizeof(device));
    printf("(Упакованная структура занимает ровно размер указателя (8 байт) + 2 байта на битовые поля = 10 байт).\n\n");

    // 2. Создание времени
    printf("--- 2. Встраивание структуры datatime ---\n");
    datatime* my_time = datatime_create_default();
    datatime_set_year(my_time, 2026);
    datatime_set_hour(my_time, 14);
    datatime_set_minute(my_time, 30);

    // 3. Создание устройства и встраивание времени
    device* smart_watch = device_create(my_time);

    // 4. Заполнение побитовых полей
    device_set_display(smart_watch, 1);       // OLED
    device_set_brightness(smart_watch, 12);   // Яркость 12
    device_set_time_format(smart_watch, 1);   // 24h
    device_set_alarm(smart_watch, 1);         // Будильник ВКЛ
    device_set_memory(smart_watch, 2);        // 64KB
    device_set_cpu(smart_watch, 0);           // ARM
    device_set_water_resist(smart_watch, 2);  // IP68

    // Вывод устройства
    device_print_info(smart_watch);

    // 5. Очистка
    printf("\n--- 5. Очистка памяти ---\n");
    device_destroy(smart_watch);
    datatime_destroy(my_time);

    return 0;
}
