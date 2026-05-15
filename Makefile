CC       = gcc
CFLAGS   = -Wall -Wextra -Werror -std=c99
CPPFLAGS = -MMD -I src -I src/libchessviz -I thirdparty

SRC_DIR  = src
LIB_SRC  = $(SRC_DIR)/libchessviz
APP_SRC  = $(SRC_DIR)/chessviz
TEST_DIR = test

OBJ_DIR  = obj
BIN_DIR  = bin

TARGET      = $(BIN_DIR)/chessviz
TEST_TARGET = $(BIN_DIR)/chessviz-test
LIB         = $(OBJ_DIR)/libchessviz.a

# Исходники
LIB_SRCS  = $(wildcard $(LIB_SRC)/*.c)
APP_SRCS  = $(wildcard $(APP_SRC)/*.c)
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)

# Объектные файлы (зеркалируют структуру каталогов внутри obj/)
LIB_OBJS  = $(patsubst $(SRC_DIR)/%.c,  $(OBJ_DIR)/%.o, $(LIB_SRCS))
APP_OBJS  = $(patsubst $(SRC_DIR)/%.c,  $(OBJ_DIR)/%.o, $(APP_SRCS))
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/$(TEST_DIR)/%.o, $(TEST_SRCS))

# Файлы зависимостей
DEPS = $(LIB_OBJS:.o=.d) $(APP_OBJS:.o=.d) $(TEST_OBJS:.o=.d)

# ──────────────────────────────────────────────

.PHONY: all test clean

all: $(BIN_DIR) $(TARGET)

test: $(BIN_DIR) $(TEST_TARGET)
	./$(TEST_TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Линковка основного приложения
$(TARGET): $(APP_OBJS) $(LIB)
	$(CC) $(CFLAGS) -o $@ $^

# Линковка тестового приложения (тесты + библиотека)
$(TEST_TARGET): $(TEST_OBJS) $(LIB)
	$(CC) $(CFLAGS) -o $@ $^

# Сборка статической библиотеки
$(LIB): $(LIB_OBJS)
	@mkdir -p $(@D)
	ar rcs $@ $^

# Компиляция объектных файлов из src/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

# Компиляция объектных файлов из test/
$(OBJ_DIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

# Подключение автоматических зависимостей заголовочных файлов
-include $(DEPS)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)/chessviz $(BIN_DIR)/chessviz-test
