#ifndef VECTOR_H
#define VECTOR_H

#include "device.h" // Подключаем структуру устройства

// Объявляем структуру вектор через typedef
typedef struct vector {
    device** data;   // Динамический массив указателей на device
    int size;        // Текущее количество элементов
    int capacity;    // Максимальная ёмкость до расширения
} vector;

// Методы вектора
vector* vector_create(int initial_capacity);
void vector_resize(vector* v, int new_capacity);
void vector_push(vector* v, device* element);
device* vector_pop(vector* v);
device* vector_get(vector* v, int index);
void vector_destroy(vector* v);

#endif
