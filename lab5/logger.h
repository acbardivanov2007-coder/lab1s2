#ifndef LOGGER_H
#define LOGGER_H
#include <stdio.h>

// Макросы для логирования
#define LOG_INFO(msg) printf("[INFO] %s:%d - %s\n", __FILE__, __LINE__, msg)
#define LOG_ERROR(msg) printf("[ERROR] %s:%d - %s\n", __FILE__, __LINE__, msg)

#endif
