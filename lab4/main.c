#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fiodevice.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Использование:\n");
        printf("  ./main save <filename> [-b]\n");
        printf("  ./main load <filename> [-b]\n");
        printf("  ./main list <filename> [-b]\n");
        printf("  ./main get <I> <filename> [-b]\n");
        return 1;
    }

    // Проверяем, есть ли флаг -b в конце
    int is_binary = (strcmp(argv[argc - 1], "-b") == 0);
    const char* cmd = argv[1];

    if (strcmp(cmd, "save") == 0) {
        const char* filename = argv[2];
        vector* my_vec = rand_gen_struct(10000); // Генерируем 10,000 элементов
        save_to_file(my_vec, filename, is_binary);
        vector_destroy(my_vec); // Очищаем память [cite: 61, 62]

    } else if (strcmp(cmd, "load") == 0) {
        const char* filename = argv[2];
        vector* my_vec = load_from_file(filename, is_binary);
        vector_destroy(my_vec);

    } else if (strcmp(cmd, "list") == 0) {
        const char* filename = argv[2];
        list_file(filename, is_binary);

    } else if (strcmp(cmd, "get") == 0) {
        if (argc < 4) { printf("Ошибка: не указан индекс для get\n"); return 1; }
        int index = atoi(argv[2]); // Переводим строку в число
        const char* filename = argv[3];
        get_element(index, filename, is_binary);

    } else {
        printf("Неизвестная команда.\n");
    }

    return 0; // Программа завершается после одной операции!
}
