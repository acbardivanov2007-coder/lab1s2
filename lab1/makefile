# Компилятор
CC = gcc
# Флаги компиляции (показывать все предупреждения)
CFLAGS = -Wall -Wextra -std=c99

# Цель по умолчанию (собирает всю программу)
all: demo

# Правило сборки исполняемого файла demo из объектных файлов .o
demo: main.o datatime.o
	$(CC) $(CFLAGS) -o demo main.o datatime.o

# Правило сборки main.o
main.o: main.c datatime.h
	$(CC) $(CFLAGS) -c main.c

# Правило сборки datatime.o
datatime.o: datatime.c datatime.h
	$(CC) $(CFLAGS) -c datatime.c

# Правило для очистки скомпилированных файлов (команда make clean)
clean:
	rm -f *.o demo
