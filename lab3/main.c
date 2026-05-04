#include <stdio.h>
#include "vector.h"

int main() {
    printf("--- Запуск демонстрации вектора устройств ---\n");

    // 1. Создаем вектор с начальной емкостью 2
    vector* my_vec = vector_create(2);
    printf("Создан вектор: size = %d, capacity = %d\n", my_vec->size, my_vec->capacity);

    // 2. Создаем устройства с разными битовыми параметрами
    device* dev1 = device_create(1, 10, 1, 1, 2, 1, 2); // Водостойкость IP68 (2), будильник ВКЛ (1)
    device* dev2 = device_create(0, 5, 0, 0, 1, 0, 0);  // Будильник ВЫКЛ (0)
    device* dev3 = device_create(2, 15, 1, 1, 3, 2, 1); // Вызовет расширение вектора!

    // 3. Добавляем устройства в вектор
    vector_push(my_vec, dev1);
    printf("Добавлено устройство 1. size = %d, capacity = %d\n", my_vec->size, my_vec->capacity);

    vector_push(my_vec, dev2);
    printf("Добавлено устройство 2. size = %d, capacity = %d\n", my_vec->size, my_vec->capacity);

    // Следующий push вызовет авто-расширение
    vector_push(my_vec, dev3);
    printf("Добавлено устройство 3. Сработало расширение! size = %d, capacity = %d\n", my_vec->size, my_vec->capacity);

    // 4. Доступ к элементу
    device* viewed_dev = vector_get(my_vec, 0);
    printf("Первое устройство: Яркость = %d, Будильник = %d\n", viewed_dev->brightness, viewed_dev->alarm_flag);

    // 5. Извлечение элемента
    device* popped_dev = vector_pop(my_vec);
    printf("Извлекли (pop) последнее устройство. Теперь size = %d\n", my_vec->size);
    // Уничтожаем извлеченное устройство вручную, так как вектор за него больше не отвечает
    device_destroy(popped_dev);

    // 6. Очистка всей оставшейся памяти
    vector_destroy(my_vec);
    printf("Память вектора и оставшихся устройств успешно освобождена.\n");

    return 0;
}
