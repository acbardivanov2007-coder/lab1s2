#include <stdio.h>
#include <stdlib.h>
#include "datatime.h" // Подключаем наш заголовочный файл со структурой

// Массив (список), где хранится количество дней в каждом месяце года.
// Индекс 0 = январь (31 день), Индекс 1 = февраль (28 дней) и так далее.
static const int days_in_months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// Скрытая (static) функция, которая проверяет, реальная ли перед нами дата.
static int is_valid_datetime(int d, int m, int y, int h, int min) {
    // Если месяц меньше 1 или больше 12, или день меньше 1, или день больше положенного в месяце,
    // или часы выходят за рамки 0-23, или минуты за рамки 0-59 — возвращаем 0 (ошибка).
    if (m < 1 || m > 12 || d < 1 || d > days_in_months[m - 1] || h < 0 || h > 23 || min < 0 || min > 59) {
        return 0; // 0 означает ложь (дата неверна)
    }
    return 1; // 1 означает истину (дата верна)
}

// Функция для создания новой структуры даты и времени в памяти компьютера
datatime* datatime_create(int d, int m, int y, int h, int min) {
    // Просим компьютер выделить нам кусочек памяти размером со структуру datatime (malloc = memory allocation)
    datatime* dt = (datatime*)malloc(sizeof(datatime));

    // Если компьютер не смог выделить память (например, она закончилась), он вернет NULL (пустоту)
    if (dt == NULL) {
        return NULL; // Выходим из функции с ошибкой
    }
    
    // Проверяем формат времени с помощью нашей скрытой функции
    if (!is_valid_datetime(d, m, y, h, min)) {
        printf("Ошибка: задан неверный формат даты или времени\n");
        free(dt); // Раз дата неверная, память нам больше не нужна, освобождаем ее
        return NULL;
    }
    
    // Если всё хорошо, заполняем структуру переданными значениями
    // Оператор -> используется для доступа к переменной внутри структуры, если у нас указатель (звездочка *)
    dt->day = d;
    dt->month = m;
    dt->year = y;
    dt->hour = h;
    dt->minute = min;

    return dt; // Отдаем созданную дату туда, откуда вызывали функцию
}

// Функция для удаления даты и освобождения оперативной памяти
void datatime_destroy(datatime **dt) {
    // Если указатель на дату не пустой (существует)
    if (dt != NULL && *dt != NULL) {
        free(*dt); // Освобождаем память с помощью команды free
        *dt = NULL; // Обнуляем указатель, чтобы случайно не попытаться обратиться к удаленной памяти
    }
}

// Создает дату, где везде стоят нули (пустая болванка)
datatime* create_empty_datatime() {
    return datatime_create(0, 0, 0, 0, 0);
}

// Функция копирует значения из даты источника (src) в дату назначения (dest)
void copy_datatime(datatime *dest, const datatime *src) {
    // Убедимся, что обе даты существуют, чтобы программа не упала
    if (dest != NULL && src != NULL) {
        dest->day = src->day;
        dest->month = src->month;
        dest->year = src->year;
        dest->hour = src->hour;
        dest->minute = src->minute;
    }
}

// Красиво печатает дату в консоль
void datatime_print(const datatime *dt) {
    if (dt != NULL) {
        // %02d означает: напечатай число (d), а если оно состоит из одной цифры, подставь спереди 0.
        // Например: 5 мая станет 05/05
        printf("[%02d/%02d/%04d %02d:%02d]\n",
                dt->day, dt->month, dt->year,
                dt->hour, dt->minute);
    }
}

// Сравнивает две даты. Возвращает -1 (если первая меньше), 1 (если первая больше), 0 (если равны)
int datatime_compare(const datatime *dt1, const datatime *dt2) {
    if (dt1 == NULL || dt2 == NULL) return 0;
 
    // Сначала сравниваем годы. Если они разные, сразу выдаем ответ
    if (dt1->year != dt2->year) return (dt1->year < dt2->year) ? -1 : 1;
    // Если годы одинаковые, смотрим на месяцы
    if (dt1->month != dt2->month) return (dt1->month < dt2->month) ? -1 : 1;
    // Если и месяцы одинаковые, смотрим на дни
    if (dt1->day != dt2->day) return (dt1->day < dt2->day) ? -1 : 1;
    // Затем часы
    if (dt1->hour != dt2->hour) return (dt1->hour < dt2->hour) ? -1 : 1;
    // И в самом конце минуты
    if (dt1->minute != dt2->minute) return (dt1->minute < dt2->minute) ? -1 : 1;

    return 0; // Если ничего не подошло, значит они полностью равны
}

// Увеличение даты на 1 минуту
void datatime_min_increment(datatime *dt) {
    if (dt == NULL) return; // Проверка на пустоту

    dt->minute++; // Увеличиваем минуту
    if (dt->minute >= 60) { // Если минут стало 60 или больше
        dt->minute = 0; // Сбрасываем минуты в ноль
        dt->hour++; // Добавляем 1 час
        if (dt->hour >= 24) { // Если часов стало 24
            dt->hour = 0; // Сбрасываем часы
            dt->day++; // Переходим на следующий день
            // Если день превысил количество дней в текущем месяце (например, стало 32 января)
            if (dt->day > days_in_months[dt->month - 1]) {
                dt->day = 1; // Ставим 1-е число
                dt->month++; // Переходим на следующий месяц
                if (dt->month > 12) { // Если месяцев стало 13
                    dt->month = 1; // Начинаем январь (1-й месяц)
                    dt->year++; // Переходим в следующий год
                }
            }
        }
    }
}

// Увеличение на 1 час (логика та же, что у минут, но начинаем с часов)
void datatime_hour_increment(datatime *dt) {
    if (dt == NULL) return;

    dt->hour++;
    if (dt->hour >= 24) {
        dt->hour = 0;
        dt->day++;
        if (dt->day > days_in_months[dt->month - 1]) {
            dt->day = 1;
            dt->month++;
            if (dt->month > 12) {
                dt->month = 1;
                dt->year++;
            }
        }
    }
}

// Увеличение на 1 день
void datatime_day_increment(datatime *dt) {
    if (dt == NULL) return;

    dt->day++;
    if (dt->day > days_in_months[dt->month - 1]) {
        dt->day = 1;
        dt->month++;
        if (dt->month > 12) {
            dt->month = 1;
            dt->year++;
        }
    }
}

// Увеличение на 1 месяц
void datatime_month_increment(datatime *dt) {
    if (dt == NULL) return;

    dt->month++;
    if (dt->month > 12) { // Переход через год, если месяцев больше 12
        dt->month = 1;
        dt->year++;
    }
}

// Увеличение на 1 год
void datatime_year_increment(datatime *dt) {
    if (dt != NULL) dt->year++;
}

// Уменьшение на 1 год
void datatime_year_decrement(datatime *dt) {
    if (dt != NULL) dt->year--;
}

// Уменьшение на 1 месяц
void datatime_month_decrement(datatime *dt) {
    if (dt == NULL) return;

    dt->month--;
    if (dt->month < 1) { // Если мы пошли назад от января (месяц 0)
        dt->month = 12; // Ставим декабрь
        dt->year--; // И отнимаем один год
    }
}

// Уменьшение на 1 день
void datatime_day_decrement(datatime *dt) {
    if (dt == NULL) return;

    dt->day--;
    if (dt->day < 1) { // Если пошли назад от 1-го числа
        dt->month--; // Откатываемся на месяц назад
        if (dt->month < 1) { // Проверяем переход через год
            dt->month = 12;
            dt->year--;
        }
        // Узнаем, сколько дней в том предыдущем месяце, куда мы откатились, и ставим последний день
        dt->day = days_in_months[dt->month - 1]; 
    }
}

// Уменьшение на 1 час
void datatime_hour_decrement(datatime *dt) {
    if (dt == NULL) return;

    dt->hour--;
    if (dt->hour < 0) { // Если отняли час от полуночи (00:00)
        dt->hour = 23; // Становится 23:00 предыдущего дня
        dt->day--; // Запускаем цепочку уменьшения дня
        if (dt->day < 1) {
            dt->month--;
            if (dt->month < 1) {
                dt->month = 12;
                dt->year--;
            }
            dt->day = days_in_months[dt->month - 1];
        }
    }
}

// Уменьшение на 1 минуту
void datatime_min_decrement(datatime *dt) {
    if (dt == NULL) return;

    dt->minute--;
    if (dt->minute < 0) { // Если отняли минуту от ровного часа (например 14:00)
        dt->minute = 59; // Становится 59 минут
        dt->hour--; // И отнимаем один час, запуская цепочку
        if (dt->hour < 0) {
            dt->hour = 23;
            dt->day--;
            if (dt->day < 1) {
                dt->month--;
                if (dt->month < 1) {
                    dt->month = 12;
                    dt->year--;
                }
                dt->day = days_in_months[dt->month - 1];
            }
        }
    }
}

// Устанавливает точное значение минут (Сеттер)
void datatime_min_set(datatime *dt, int min) {
    if (dt != NULL) {
        // Проверяем, чтобы мы не вписали 100 минут, например
        if(min >= 0 && min < 60) dt->minute = min;
        else printf("Ошибка: недопустимое значение минут\n");
    }
}

// Устанавливает точное значение часов (Сеттер)
void datatime_hour_set(datatime *dt, int h) {
    if (dt != NULL) {
        if(h >= 0 && h < 24) dt->hour = h;
        else printf("Ошибка: недопустимое значение часов\n");
    }
}

// Устанавливает точное значение дней (Сеттер)
void datatime_day_set(datatime *dt, int d) {
    if (dt != NULL) {
        if(d >= 1 && d <= days_in_months[dt->month - 1]) dt->day = d;
        else printf("Ошибка: недопустимое значение дней\n");
    }
}

// Устанавливает точное значение месяца (Сеттер)
void datatime_month_set(datatime *dt, int m) {
    if (dt != NULL) {
        if(m >= 1 && m <= 12) dt->month = m;
        else printf("Ошибка: недопустимое значение месяца\n");
    }
}

// Устанавливает год (ограничений на год нет)
void datatime_year_set(datatime *dt, int y) {
    if (dt != NULL) {
        dt->year = y;
    }
}

// Преобразует структуру в красивую строку текста
char* datatime_to_string(const datatime *dt) {
    if (dt == NULL) return NULL;

    // Выделяем память под текст (20 символов хватит для формата ДД/ММ/ГГГГ ЧЧ:ММ и скрытого символа конца строки)
    char* buffer = (char*)malloc(20 * sizeof(char));
    if (buffer == NULL) return NULL;

    // snprintf "печатает" значения не в консоль, а внутрь текстовой переменной buffer
    snprintf(buffer, 20, "%02d/%02d/%04d %02d:%02d",
                dt->day, dt->month, dt->year,
                dt->hour, dt->minute);

    return buffer; // Возвращаем получившийся текст
}

// Делает обратное: читает текст и создает из него структуру
datatime* datatime_from_string(const char *str) {
    if (str == NULL) return NULL;

    int d, m, y, h, min;
    // sscanf "сканирует" строку текста и ищет в ней числа по заданному шаблону "%d/%d/%d %d:%d"
    // Если он нашел не 5 чисел, значит строка была с ошибкой
    if (sscanf(str, "%d/%d/%d %d:%d", &d, &m, &y, &h, &min) != 5) {
        return NULL;
    }

    // Проверяем, нормальные ли числа мы вытащили из текста (не 99 месяц ли там?)
    if(!is_valid_datetime(d, m, y, h, min)) {
        printf("Ошибка парсинга: неверный формат строки\n");
        return NULL;
    }

    // Создаем структуру на основе прочитанных чисел
    return datatime_create(d, m, y, h, min);
}

// Переводит всю дату в одно огромное число — количество минут с нулевого года
// Это очень удобно для того, чтобы узнать точную разницу между двумя датами
unsigned long long datatime_to_minutes(const datatime *dt) {
    if (dt == NULL) return 0;

    unsigned long long total_mins = 0; // Переменная для подсчета (очень большая, чтобы влезло)
    total_mins += dt->year * 365 * 24 * 60; // Превращаем годы в минуты

    // Пробегаемся по всем прошедшим месяцам текущего года и добавляем их дни (в виде минут)
    for (int m = 0; m < dt->month; m++) {
        total_mins += days_in_months[m] * 24 * 60;
    }

    // Добавляем оставшиеся дни, часы и минуты
    total_mins += (dt->day - 1) * 24 * 60;
    total_mins += dt->hour * 60;
    total_mins += dt->minute;

    return total_mins; // Отдаем огромное число минут
}

// Обратный процесс: из огромного количества минут собираем нормальную дату
datatime* datatime_from_minutes(unsigned long long total_minutes) {
    datatime* dt = (datatime*)malloc(sizeof(datatime));
    if (dt == NULL) return NULL;

    // Начинаем отсчет с "начала времен"
    dt->year = 1;
    dt->month = 1;
    dt->day = 1;
    dt->hour = 0;
    dt->minute = 0;

    // Сколько минут в целом году (не учитывая високосные для простоты)
    unsigned long long mins_in_year = 365 * 24 * 60;

    // Пока общее число минут больше года, отнимаем год минут и прибавляем год к нашей дате
    while (total_minutes >= mins_in_year) {
        total_minutes -= mins_in_year;
        dt->year++;
    }

    // Раскидываем остаток по месяцам
    while (dt->month <= 12) {
        unsigned long long mins_in_month = days_in_months[dt->month - 1] * 24 * 60;
        if (total_minutes >= mins_in_month) {
            total_minutes -= mins_in_month;
            dt->month++;
        } else {
            break; // Если минут меньше, чем дней в текущем месяце, останавливаемся
        }
    }

    // Раскидываем остаток по дням
    unsigned long long mins_in_day = 24 * 60;
    while (total_minutes >= mins_in_day) {
        total_minutes -= mins_in_day;
        dt->day++;
    }

    // Все, что осталось (меньше дня) — это просто делим на 60 (получаем часы) и берем остаток (получаем минуты)
    dt->hour = total_minutes / 60;
    dt->minute = total_minutes % 60;

    return dt;
}

// Красиво считает и выводит на экран, сколько лет, месяцев, дней прошло между двумя датами
void datatime_print_diff(const datatime *dt1, const datatime *dt2) {
    if (dt1 == NULL || dt2 == NULL) {
        printf("Ошибка вычисления: передан пустой указатель (NULL)\n");
        return;
    }

    // Определяем, какая дата была раньше, а какая позже (чтобы не получать отрицательное время)
    const datatime *early_dt = dt1;
    const datatime *late_dt = dt2;
    
    // Если первая дата больше второй, меняем их местами
    if (datatime_compare(dt1, dt2) > 0) {
        early_dt = dt2;
        late_dt = dt1;
    }

    // Вычитаем в лоб каждую часть
    int years = late_dt->year - early_dt->year;
    int months = late_dt->month - early_dt->month;
    int days = late_dt->day - early_dt->day;
    int hours = late_dt->hour - early_dt->hour;
    int minutes = late_dt->minute - early_dt->minute;

    // Если при вычитании минут получилось отрицательное число (например 10 минут - 30 минут = -20)
    if (minutes < 0) {
        minutes += 60; // "Занимаем" 60 минут у часов
        hours--;       // Соответственно, часов становится на 1 меньше
    }
    // То же самое "занимание" делаем для часов у дней...
    if (hours < 0) {
        hours += 24;
        days--;
    }
    // ...для дней у месяцев...
    if (days < 0) {
        months--;
        // Занимаем ровно столько дней, сколько было в предыдущем месяце ранней даты
        days += days_in_months[early_dt->month - 1];
    }
    // ...и для месяцев у годов.
    if (months < 0) {
        years--;
        months += 12;
    }

    // Печатаем результат пользователю
    printf("Временной интервал составляет:\n");
    printf("-> Лет: %d\n", years);
    printf("-> Месяцев: %d\n", months);
    printf("-> Дней: %d\n", days);
    printf("-> Часов: %d\n", hours);
    printf("-> Минут: %d\n", minutes);
}

// Функция меняет значения двух дат местами (классическая замена через третью пустую переменную)
void datatimes_switch(datatime *dt1, datatime *dt2) {
    if (dt1 == NULL || dt2 == NULL) return;

    datatime temp; // Временная "коробка"
    copy_datatime(&temp, dt1); // Кладем в коробку первую дату
    copy_datatime(dt1, dt2);   // В первую дату кладем вторую (первая стерлась, но она есть в коробке)
    copy_datatime(dt2, &temp); // Во вторую дату кладем то, что сохраняли в коробке
}
