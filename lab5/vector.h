#ifndef VECTOR_H
#define VECTOR_H
#include "device.h"
#include <stddef.h> // Для size_t

typedef struct {
    device** data;     // Указатель на массив указателей на устройства
    size_t size;       // Текущее количество
    size_t capacity;   // Максимальная вместимость
} vector;

vector* vector_create(size_t initial_capacity);
void vector_push(vector* v, device* dev);
void vector_destroy(vector* v);

#endif
