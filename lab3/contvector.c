#include <stdlib.h>
#include "vector.h"

// Создание вектора
vector* vector_create(int initial_capacity) {
    if (initial_capacity <= 0) {
        initial_capacity = 1; // Инициализация не нулевым значением
    }

    // Выделяем память под саму "коробку" вектора
    vector* v = (vector*)malloc(sizeof(vector));
    
    // Выделяем память под массив указателей на устройства
    v->data = (device**)malloc(initial_capacity * sizeof(device*));
    v->size = 0;
    v->capacity = initial_capacity;

    return v;
}

// Изменение ёмкости вектора
void vector_resize(vector* v, int new_capacity) {
    // realloc расширяет старый массив, сохраняя данные
    v->data = (device**)realloc(v->data, new_capacity * sizeof(device*));
    v->capacity = new_capacity;
}

// Добавление элемента (устройства) в конец
void vector_push(vector* v, device* element) {
    // Если места нет, увеличиваем ёмкость в 2 раза
    if (v->size == v->capacity) {
        vector_resize(v, v->capacity * 2);
    }
    
    v->data[v->size] = element;
    v->size++;
}

// Извлечение (удаление из вектора) последнего элемента
device* vector_pop(vector* v) {
    if (v->size == 0) {
        return NULL;
    }
    
    v->size--; // Уменьшаем размер
    return v->data[v->size]; // Возвращаем извлеченный элемент
}

// Получение элемента по индексу
device* vector_get(vector* v, int index) {
    if (index < 0 || index >= v->size) return NULL;
    return v->data[index];
}

// Деструктор (освобождение памяти)
void vector_destroy(vector* v) {
    // Сначала удаляем все устройства внутри
    for (int i = 0; i < v->size; i++) {
        device_destroy(v->data[i]);
    }
    // Удаляем массив указателей
    free(v->data);
    // Удаляем саму структуру вектора
    free(v);
}
