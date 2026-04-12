// Подключаем наш заголовочный файл, чтобы программа знала наши структуры и функции
#include "bitstruct.h"

// Создаем списки (массивы) с ценами на компоненты. Const означает, что их нельзя менять.
const int display_price[] = {1000, 1500, 3000, 2500};
const int cpu_price[] = {1000, 1500, 3000, 2500};
const int memory_price[] = {1000, 1500, 3000, 2500};
const int water_price[] = {1000, 1500, 3000, 2500};

// Создаем списки с названиями компонентов (текст).
const char* display_names[] = {"LCD", "LED", "OLED", "E-Ink"};
const char* cpu_names[] = {"ARM", "AVR", "M-16pro", "x86"};
const char* memory_names[] = {"16KB", "32KB", "64KB", "128KB"};
const char* water_names[] = {"Нет", "IP67", "IP68"};

// Функция для создания нового устройства в памяти
device* dev_create (void) {
    // Просим у компьютера кусочек памяти размером со структуру device
    device* d = malloc(sizeof(device));
    
    // Если память не выдалась (например, ее нет), возвращаем "пустоту" (NULL)
    if (d == NULL) {
        return NULL;
    }
    
    // Изначально обнуляем все побитовые поля, чтобы там не было случайного мусора
    d->data.display = 0;
    d->data.brightness = 0;
    d->data.time_format = 0;
    d->data.alarm = 0;
    d->data.memory = 0;
    d->data.cpu = 0;
    d->data.water = 0;
    
    // Возвращаем адрес свежесозданного устройства
    return d;
}

// Функция для уничтожения устройства (чтобы память не засорялась)
void dev_destroy (device* d) {
    // Команда free возвращает память обратно компьютеру
    free(d);
}

// --- ФУНКЦИИ ЗАПИСИ (СЕТТЕРЫ) ---
// Записываем тип дисплея. Принимаем адрес устройства (d) и значение (val)
void dev_set_display (device* d, uint16_t val) {
    if(d == NULL) return; // Если устройства не существует, ничего не делаем
    if(val > 7) return;   // Защита: в 3 бита нельзя записать число больше 7
    d->data.display = val; // Просто записываем значение прямо в битовое поле
}

void dev_set_brightness(device* d, uint16_t value) {
    if (d == NULL) return;
    if (value > 15) return; // Защита: в 4 бита влезает максимум 15
    d->data.brightness = value; // Записываем яркость
}

void dev_set_time_format(device* d, uint16_t value) {
    if (d == NULL) return;
    if (value > 1) return; // Защита: 1 бит - это только 0 или 1
    d->data.time_format = value;
}

void dev_set_alarm(device* d, uint16_t value) {
    if (d == NULL) return;
    if (value > 1) return; // 0 (выключен) или 1 (включен)
    d->data.alarm = value;
}

void dev_set_memory(device* d, uint16_t value) {
    if (d == NULL) return;
    if (value > 3) return; // В 2 бита влезает максимум 3
    d->data.memory = value;
} 

void dev_set_cpu(device* d, uint16_t value) {
    if (d == NULL) return;
    if (value > 7) return; 
    d->data.cpu = value;
}

void dev_set_water(device* d, uint16_t value) {
    if (d == NULL) return;
    if (value > 3) return;
    d->data.water = value; 
}

// --- ФУНКЦИИ ЧТЕНИЯ (ГЕТТЕРЫ) ---
// Читаем тип дисплея из устройства
uint16_t dev_get_display (device* d) {
    if (d == NULL) return 0; // Если устройства нет, возвращаем 0
    return d->data.display;  // Просто отдаем то, что лежит в битовом поле
}

uint16_t dev_get_brightness (device* d) {
    if (d == NULL) return 0;
    return d->data.brightness;
}

uint16_t dev_get_time_format (device* d) {
    if (d == NULL) return 0;
    return d->data.time_format;
}

uint16_t dev_get_alarm (device* d) {
    if (d == NULL) return 0;
    return d->data.alarm;
}

uint16_t dev_get_memory (device* d) {
    if (d == NULL) return 0;    
    return d->data.memory;
}

uint16_t dev_get_cpu (device* d) {
    if (d == NULL) return 0;
    return d->data.cpu;
}

uint16_t dev_get_water (device* d) {
    if (d == NULL) return 0;
    return d->data.water;
}

// Умная функция, которая заставляет пользователя ввести правильное число
int get_choice(uint16_t min, uint16_t max) {
    uint16_t val; // Сюда положим введенное число
    int res;      // Сюда положим результат работы считывания

    while (1) { // Запускаем бесконечный цикл (будем мучить пользователя, пока не введет верно)
        // Пытаемся считать число с клавиатуры
        res = scanf("%hu", &val);

        // Если пользователь ввел буквы вместо цифр (res != 1 означает, что считать число не вышло)
        if (res != 1) {
            // Очищаем буфер клавиатуры от мусора (букв), считывая их до переноса строки
            while (getchar() != '\n'); 
            printf("Ошибка ввода. Попробуйте снова: "); // Ругаемся
            continue; // Начинаем цикл заново
        }

        // Если число меньше минимума или больше максимума
        if (val < min || val > max) {
            printf("Недопустимое значение. Попробуйте снова: ");
            continue; // Начинаем цикл заново
        }

        // Если всё идеально - возвращаем введенное число и выходим из функции
        return val;
    }
}
