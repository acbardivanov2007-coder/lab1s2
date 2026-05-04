#ifndef FIODEVICE_H
#define FIODEVICE_H
#include "vector.h"

// Генерация 10000 элементов
vector* rand_gen_struct(size_t n);

// Сохранение и загрузка
void save_to_file(vector* v, const char* filename, int is_binary);
vector* load_from_file(const char* filename, int is_binary);

// Список и получение i-того элемента
void list_file(const char* filename, int is_binary);
void get_element(int index, const char* filename, int is_binary);
device* get_element_from_text_file(const char* filename, int index);

#endif
