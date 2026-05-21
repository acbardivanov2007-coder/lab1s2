#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "fiodevice.h"
#include "logger.h" // Подключаем наш логгер

// Функция для демонстрации Юнит-тестов
void run_unit_tests() {
    LOG_INFO("Запуск Юнит-тестов...");
    
    // 1. Правильное тестирование: проверяем, что вектор создается корректно
    vector* test_vec = vector_create(5);
    assert(test_vec != NULL); // Проверка: память выделилась
    assert(test_vec->capacity == 5); // Проверка: вместимость верная
    assert(test_vec->size == 0); // Проверка: элементов пока нет
    
    device* test_dev = device_create();
    assert(test_dev != NULL);
    vector_push(test_vec, test_dev);
    assert(test_vec->size == 1); // Проверка: элемент добавился
    
    vector_destroy(test_vec);
    LOG_INFO("Юнит-тесты пройдены успешно!");

    // 2. Пример НЕПРАВИЛЬНОГО тестирования (раскомментируйте для демонстрации ошибки)
    // LOG_INFO("Демонстрация проваленного теста...");
    // vector* fail_vec = vector_create(0);
    // assert(fail_vec->capacity == 100); // ОШИБКА: Ожидаем 100, а по факту 1. Программа экстренно упадет!
}

int main(int argc, char* argv[]) {
    // Вызов тестов перед основной работой
    run_unit_tests();

    if (argc < 3) {
        LOG_ERROR("Недостаточно аргументов!");
        printf("Использование:\n  ./main save <filename> [-b]\n  ./main load <filename> [-b]\n  ./main list <filename> [-b]\n  ./main get <I> <filename> [-b]\n");
        return 1;
    }

    int is_binary = (strcmp(argv[argc - 1], "-b") == 0);
    const char* cmd = argv[1];

    if (strcmp(cmd, "save") == 0) {
        LOG_INFO("Начало генерации данных...");
        const char* filename = argv[2];
        vector* my_vec = rand_gen_struct(10000); 
        save_to_file(my_vec, filename, is_binary);
        vector_destroy(my_vec); 
        LOG_INFO("Сохранение и очистка завершены.");

    } else if (strcmp(cmd, "load") == 0) {
        // ... (остальной код из вашего main.c остается без изменений)
        const char* filename = argv[2];
        vector* my_vec = load_from_file(filename, is_binary);
        vector_destroy(my_vec);

    } else if (strcmp(cmd, "list") == 0) {
        const char* filename = argv[2];
        list_file(filename, is_binary);

    } else if (strcmp(cmd, "get") == 0) {
        if (argc < 4) { printf("Ошибка: не указан индекс для get\n"); return 1; }
        int index = atoi(argv[2]); 
        const char* filename = argv[3];
        get_element(index, filename, is_binary);

    } else {
        printf("Неизвестная команда.\n");
    }

    return 0; 
}
