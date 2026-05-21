CC = gcc
# Базовые флаги + отладочная информация
CFLAGS = -Wall -Wextra -g

all: demo

# Сборка без оптимизации (Для задания на 3)
demo: main.o fiodevice.o vector.o device.o
	$(CC) $(CFLAGS) -O0 -o main main.o fiodevice.o vector.o device.o

# Сборка с разными уровнями оптимизации (Для задания на 4)
demo_O1: CFLAGS += -O1
demo_O1: clean demo

demo_O2: CFLAGS += -O2
demo_O2: clean demo

demo_O3: CFLAGS += -O3
demo_O3: clean demo

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

fiodevice.o: fiodevice.c
	$(CC) $(CFLAGS) -c fiodevice.c

vector.o: vector.c
	$(CC) $(CFLAGS) -c vector.c

device.o: device.c
	$(CC) $(CFLAGS) -c device.c

clean:
	rm -f *.o main
