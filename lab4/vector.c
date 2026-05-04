#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

// 1. Создание вектора
vector* vector_create(size_t initial_capacity) {
    // Просим у системы (кучи/heap) блок памяти для хранения самой "коробки" вектора [cite: 99]
    vector* v = (vector*)malloc(sizeof(vector));
    if (v == NULL) return NULL;
    
    v->size = 0; // Пока элементов ноль
    v->capacity = initial_capacity > 0 ? initial_capacity : 1; // Защита от нулевой вместимости
    
    // Мы просим место под массив ячеек, в которые потом положим адреса устройств [cite: 101]
    v->data = (device**)malloc(v->capacity * sizeof(device*));
    
    return v;
}

// 2. Внутренняя функция расширения вектора (скрыта от пользователя)
static void vector_resize(vector* v, size_t new_capacity) {
    // Этот инструмент берет наш старый массив, ищет в памяти кусок побольше, копирует туда старые элементы [cite: 104]
    device** new_data = (device**)realloc(v->data, new_capacity * sizeof(device*));
    if (new_data != NULL) {
        v->data = new_data; // Обновляем указатель на новый массив
        v->capacity = new_capacity; // Обновляем значение вместимости
    }
}

// 3. Добавление элемента (устройства) в конец вектора
void vector_push(vector* v, device* dev) {
    if (v == NULL || dev == NULL) return;
    
    // Если количество элементов достигло максимума, мы вызываем функцию расширения и умножаем текущую вместимость на 2 [cite: 103]
    if (v->size == v->capacity) {
        vector_resize(v, v->capacity * 2);
    }
    
    // Кладем адрес устройства в первую свободную ячейку
    v->data[v->size] = dev; 
    v->size++; // Увеличиваем счетчик элементов
}

// 4. Освобождение памяти вектора (Деструктор)
void vector_destroy(vector* v) {
    if (v == NULL) return;
    
    // ВАЖНО: Сначала мы должны удалить все устройства, адреса которых лежат в массиве!
    for (size_t i = 0; i < v->size; i++) {
        device_destroy(v->data[i]);
    }
    
    // Затем удаляем сам массив адресов
    free(v->data);
    
    // И только в самом конце удаляем "коробку" вектора
    free(v);
}
