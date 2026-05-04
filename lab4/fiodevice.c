#include "fiodevice.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 1. Генерация n случайных структур
vector* rand_gen_struct(size_t n) {
    vector* v = vector_create(n); // Создаем вектор нужной вместимости
    srand(time(NULL)); // Инициализируем генератор случайных чисел
    
    for (size_t i = 0; i < n; i++) {
        device* dev = device_create();
        // Заполняем побитовые поля случайными значениями в пределах их бит
        dev->display_type = rand() % 4;
        dev->brightness = rand() % 16;
        dev->time_format = rand() % 2;
        dev->alarm_flag = rand() % 2;
        dev->memory = rand() % 4;
        dev->cpu_type = rand() % 4;
        dev->water_resistance = rand() % 3;
        
        vector_push(v, dev); // Кладем в вектор
    }
    return v;
}

// 2. Сохранение вектора в файл (Обычный текстовый или бинарный)
void save_to_file(vector* v, const char* filename, int is_binary) {
    // Выбираем режим: "wb" - запись в бинарном, "w" - запись в текстовом
    FILE* file = fopen(filename, is_binary ? "wb" : "w");
    if (!file) {
        printf("Ошибка открытия файла для записи!\n");
        return;
    }

    if (is_binary) {
        // Бинарный режим: пишем куски памяти напрямую
        for (size_t i = 0; i < v->size; i++) {
            // Пишем 1 структуру размером sizeof(device) в файл
            fwrite(v->data[i], sizeof(device), 1, file);
        }
    } else {
        // Текстовый режим: форматируем данные как строку (CSV)
        for (size_t i = 0; i < v->size; i++) {
            fprintf(file, "%u %u %u %u %u %u %u\n",
                    v->data[i]->display_type, v->data[i]->brightness,
                    v->data[i]->time_format, v->data[i]->alarm_flag,
                    v->data[i]->memory, v->data[i]->cpu_type,
                    v->data[i]->water_resistance);
        }
    }
    fclose(file); // Закрываем файл после работы
    printf("Сохранено %zu элементов в файл '%s' (%s)\n", v->size, filename, is_binary ? "бинарный" : "текстовый");
}

// 3. Извлечение i-того объекта из текстового файла построчно
device* get_element_from_text_file(const char* filename, int index) {
    FILE* file = fopen(filename, "r"); // "r" - чтение текста
    if (!file) return NULL;

    device* dev = device_create();
    int current_index = 0;
    unsigned int d_type, br, tf, af, mem, cpu, wr; // Временные переменные

    // Читаем файл построчно до конца
    while (fscanf(file, "%u %u %u %u %u %u %u", &d_type, &br, &tf, &af, &mem, &cpu, &wr) == 7) {
        if (current_index == index) { // Нашли нужный индекс!
            dev->display_type = d_type;
            dev->brightness = br;
            dev->time_format = tf;
            dev->alarm_flag = af;
            dev->memory = mem;
            dev->cpu_type = cpu;
            dev->water_resistance = wr;
            fclose(file);
            return dev; // Возвращаем собранный объект
        }
        current_index++;
    }
    
    fclose(file);
    device_destroy(dev); // Если индекс не найден, очищаем память
    return NULL; 
}

// 4. Получение i-того элемента (универсальное для текста и бинарника)
void get_element(int index, const char* filename, int is_binary) {
    device* dev = NULL;
    
    if (is_binary) {
        FILE* file = fopen(filename, "rb");
        if (!file) { printf("Ошибка файла!\n"); return; }
        
        dev = device_create();
        // fseek - перемещение по файлу. Сдвигаемся на (index * размер_одной_структуры) от начала
        fseek(file, index * sizeof(device), SEEK_SET);
        if (fread(dev, sizeof(device), 1, file) != 1) {
            printf("Индекс %d выходит за границы бинарного файла.\n", index);
            device_destroy(dev);
            fclose(file);
            return;
        }
        fclose(file);
    } else {
        // Для текста вызываем нашу специальную функцию
        dev = get_element_from_text_file(filename, index);
    }

    if (dev) {
        printf("Элемент [%d]:\n", index);
        device_print(dev);
        device_destroy(dev);
    } else {
        printf("Индекс %d выходит за границы текстового файла.\n", index);
    }
}

// 5. Вывод списка и количества
void list_file(const char* filename, int is_binary) {
    FILE* file = fopen(filename, is_binary ? "rb" : "r");
    if (!file) { printf("Файл не найден!\n"); return; }

    int count = 0;
    device dev;

    if (is_binary) {
        // Читаем по одной структуре, пока файл не кончится
        while (fread(&dev, sizeof(device), 1, file) == 1) {
            printf("[%d] ", count);
            device_print(&dev);
            count++;
        }
    } else {
        unsigned int d_type, br, tf, af, mem, cpu, wr;
        // Читаем текст построчно
        while (fscanf(file, "%u %u %u %u %u %u %u", &d_type, &br, &tf, &af, &mem, &cpu, &wr) == 7) {
            dev.display_type = d_type; dev.brightness = br; dev.time_format = tf;
            dev.alarm_flag = af; dev.memory = mem; dev.cpu_type = cpu; dev.water_resistance = wr;
            
            printf("[%d] ", count);
            device_print(&dev);
            count++;
        }
    }
    printf("Всего элементов: %d\n", count);
    fclose(file);
}

// Загрузка всего файла в вектор
vector* load_from_file(const char* filename, int is_binary) {
    vector* v = vector_create(10);
    FILE* file = fopen(filename, is_binary ? "rb" : "r");
    if (!file) { printf("Файл не найден!\n"); return v; }

    if (is_binary) {
        device temp_dev;
        while (fread(&temp_dev, sizeof(device), 1, file) == 1) {
            device* dev = device_create();
            *dev = temp_dev; // Копируем данные
            vector_push(v, dev);
        }
    } else {
        unsigned int d_type, br, tf, af, mem, cpu, wr;
        while (fscanf(file, "%u %u %u %u %u %u %u", &d_type, &br, &tf, &af, &mem, &cpu, &wr) == 7) {
            device* dev = device_create();
            dev->display_type = d_type; dev->brightness = br; dev->time_format = tf;
            dev->alarm_flag = af; dev->memory = mem; dev->cpu_type = cpu; dev->water_resistance = wr;
            vector_push(v, dev);
        }
    }
    fclose(file);
    printf("Загружено %zu элементов.\n", v->size);
    return v;
}
