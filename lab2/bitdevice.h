#ifndef DEVICE_H // Защита от двойного включения
#define DEVICE_H

// Объявляем структуру device с использованием typedef, чтобы писать короче
typedef struct device {
    // После двоеточия мы указываем количество БИТ, которое займет переменная
    unsigned int display_type : 2;      // Тип дисплея (хватит 2 бита для 4 вариантов: 0-3)
    unsigned int brightness : 4;        // Яркость экрана (4 бита для 16 уровней: от 0 до 15)
    unsigned int time_format : 1;       // Формат времени (1 бит: 0 = 12h, 1 = 24h)
    unsigned int alarm_flag : 1;        // Будильник (1 бит: 0 = выкл, 1 = вкл)
    unsigned int memory_size : 2;       // Память (2 бита: 0=16KB, 1=32KB, 2=64KB, 3=128KB)
    unsigned int processor_type : 2;    // Тип процессора (2 бита для 4 вариантов: 0-3)
    unsigned int water_resistance : 2;  // Водостойкость (2 бита: 0=Нет, 1=IP67, 2=IP68)
} device;

// Объявления "конструктора", "деструктора" и методов
device* device_create(void); 
void device_destroy(device* dev);
// Метод-сеттер для заполнения полей
void device_setup(device* dev, unsigned int disp, unsigned int bright, unsigned int fmt, 
                  unsigned int alarm, unsigned int mem, unsigned int proc, unsigned int water);
void device_print(const device* dev);

#endif
