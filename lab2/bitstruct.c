#include "bitstruct.h"

const int display_price[] = {1000, 1500, 3000, 2500};
const int cpu_price[] = {1000, 1500, 3000, 2500};
const int memory_price[] = {1000, 1500, 3000, 2500};
const int water_price[] = {1000, 1500, 3000, 2500};

const char* display_names[] = {"LCD", "LED", "OLED", "E-Ink"};
const char* cpu_names[] = {"ARM", "AVR", "M-16pro", "x86"};
const char* memory_names[] = {"16KB", "32KB", "64KB", "128KB"};
const char* water_names[] = {"Нет", "IP67", "IP68"};

device* dev_create (void) {
    device* d = malloc(sizeof(device));
    if (d == NULL) {
        return NULL;
    }
    // Инициализация побитовых полей нулями
    d->data.display = 0;
    d->data.brightness = 0;
    d->data.time_format = 0;
    d->data.alarm = 0;
    d->data.memory = 0;
    d->data.cpu = 0;
    d->data.water = 0;
    
    return d;
}

void dev_destroy (device* d) {
    free(d);
}

// Теперь запись происходит напрямую в битовые поля структуры, без сдвигов и масок (Оценка 3)
void dev_set_display (device* d, uint16_t val) {
    if(d == NULL) return;
    if(val > 7) return; 
    d->data.display = val; 
}

void dev_set_brightness(device* d, uint16_t value) {
    if (d == NULL) return;
    if (value > 15) return;
    d->data.brightness = value;
}

void dev_set_time_format(device* d, uint16_t value) {
    if (d == NULL) return;
    if (value > 1) return;
    d->data.time_format = value;
}

void dev_set_alarm(device* d, uint16_t value) {
    if (d == NULL) return;
    if (value > 1) return;
    d->data.alarm = value;
}

void dev_set_memory(device* d, uint16_t value) {
    if (d == NULL) return;
    if (value > 3) return;
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

// Чтение также идет напрямую из битовых полей
uint16_t dev_get_display (device* d) {
    if (d == NULL) return 0;
    return d->data.display; 
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

int get_choice(uint16_t min, uint16_t max) {
    uint16_t val;
    int res;

    while (1) {
        res = scanf("%hu", &val);

        if (res != 1) {
            while (getchar() != '\n'); 
            printf("Ошибка ввода. Попробуйте снова: ");
            continue;
        }

        if (val < min || val > max) {
            printf("Недопустимое значение. Попробуйте снова: ");
            continue;
        }

        return val;
    }
}
